/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:59:59 by razouani          #+#    #+#             */
/*   Updated: 2025/03/19 22:09:12 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	creat_node(char *type, t_token *token, char *value,
		t_minishell *minishell)
{
	if (ft_strcmp(type, "commande") == 0)
		minishell->flag = 1;
	if (ft_strcmp(type, "pipe") == 0)
		minishell->flag = 0;
	token->type = ft_strdup(type);
	if (!token->type)
		return ;
	token->value = ft_strdup(value);
	if (!token->value)
		return ;
	token->next = ft_calloc(sizeof(t_token), 1);
	if (!token->next)
		return ;
}


static int get_line(t_minishell *minishell, int *index)
{
	int i;

	i = *index;
	while(((minishell->buffer[i] == '<') || (minishell->buffer[i] == ' ')) && (minishell->buffer[i]))
		i++;
	while((minishell->buffer[i] != ' ') && (minishell->buffer[i]))
		i++;
	return(i - *index);
}

static void cas_spe(t_minishell *minishell, int *index, int flag)
{
	int j;
	int len;

	j = 0;
	if(flag == 1)
	{
		minishell->current = ft_calloc(sizeof(char), 2);
		if (!minishell->current)
			return ;
		minishell->current[0] = minishell->buffer[*index];
		minishell->current[1] = '\0';
		*index +=1;
	}
	else if (flag == 2)
	{
		len = get_line(minishell, index);
		minishell->current = ft_calloc(sizeof(char), len+ 1);
		while(j < len)
		{
			minishell->current[j] = minishell->buffer[*index];
			*index += 1;
			j++;
		}
	}
}


static int creat_current(t_minishell *minishell, int *index, int i, int j, int y)
{
	int len;

	len = i - *index;
	if (len <= 0)
		return (1);
	minishell->current = ft_calloc(sizeof(char), len + 1);
	if (!minishell->current)
	return (1);
	while (j < len && minishell->buffer[*index])
	{
		minishell->current[j] = minishell->buffer[*index];
		if (minishell->buffer[*index] == 34 || minishell->buffer[*index] == 39)
		{
			clear_quote(minishell->buffer, minishell->current,  index, y, &j);
			return (0);
		}
		*index += 1;
		j++;
	}
	minishell->current[j] = '\0';
	return (0);
}

static int	grap_mot(t_minishell *minishell, int *index)
{
	int	i;
	int	j;
	int	y;

	i = *index;
	y = *index;
	j = 0;
	if (is_space(minishell->buffer, &i) == -1)
		return(cas_spe(minishell, index, 2), 0);
	else if(is_space(minishell->buffer, &i) == 0)
		return(cas_spe(minishell, index, 1), 0);
	while(minishell->buffer[i] && (is_space(minishell->buffer, &i) == 1) && minishell->buffer[i] != '\t')
	{
		if ((minishell->buffer[i] ==  39 || minishell->buffer[i] == 34) && minishell->buffer[i + 1])
		{
			i++;
			while (minishell->buffer[i] && (minishell->buffer[i] !=  39 && minishell->buffer[i] != 34))
				i++;
		}
		else
			i++;
	}
	if(creat_current(minishell, index, i, j, y) == 1)
		return(1);
	return (0);
}

static int	get_type(char *mot, t_token *token, t_pipex *pipex,
		t_minishell *minishell)
{
	if (mot[0] == '<')
		if(mot[1] == '<')
			return(creat_node("heredoc", token, mot, minishell), 0);
	if ((ft_strcmp(mot, ">") == 0) || (ft_strcmp(mot, "<") == 0) || (ft_strcmp(mot, ">>") == 0))
	{
		if (ft_strcmp(mot, ">") == 0 || (ft_strcmp(mot, ">>") == 0))
			return (creat_node("redirect output", token, mot, minishell), 0);
		else if (ft_strcmp(mot, "<") == 0)
			return (creat_node("redirect input", token, mot, minishell), 0);
	}
	else if (minishell->flag == 1)
	{
		if (ft_strcmp(mot, "|") == 0)
			return (creat_node("pipe", token, mot, minishell), 0);
		return (creat_node("argument", token, mot, minishell), 0);
	}
	else if (search_command_for_token(pipex, mot) == 0)
		return (creat_node("commande", token, mot, minishell), 0);
	else if (ft_strcmp(mot, "|") == 0)
		return (creat_node("pipe", token, mot, minishell), 0);
	else
		return (creat_node("trash", token, mot, minishell), 0);
	return (1);
}

static void	get_double_cot(char *mot, t_token *token, t_pipex *pipex, int chef,
		t_minishell *minishell)
{
	char	*in_cot;
	int		i;
	int		c;

	i = 0;
	c = 0;
	in_cot = in_quote(mot, chef);
	while (in_cot[i])
	{
		if (mot[i] == ' ')
			c++;
		i++;
	}
	if (c == 0)
	{
		if (get_type(mot, token, pipex, minishell) == 0)
			return ;
		else
			creat_node("string", token, mot, minishell);
	}
}

static void duplicate_in(t_minishell *minishell, t_token *token)
{
	int i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (token->next != NULL)
	{
		minishell->command_exac[i] = ft_strdup(token->value);
		if (!minishell->command_exac[i])
		{
		    while (i > 0)
		        free(minishell->command_exac[--i]);
		    free(minishell->command_exac);
		    minishell->command_exac = NULL;
		    return;
		}
		token = token->next;
		i++;
	}
	minishell->command_exac[i] = NULL;
	token = tmp;
}

static void	put_in(t_token *token, t_minishell *minishell)
{
	t_token	*tmp;
	int		len;

	if (!token || !minishell)
        return;
	tmp = token;
	len = 0;
	while (tmp && token->next != NULL)
	{
		token = token->next;
		len++;
	}
	token = tmp;
	minishell->command_exac = ft_calloc(sizeof(char *), len + 1);
	if (!minishell->command_exac)
		return ;
	duplicate_in(minishell, token);
}

static int creat_lst(t_token *token, t_minishell *minishell, t_pipex *pipex)
{
	int i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (minishell->buffer[i])
	{
		while((minishell->buffer[i] == ' ' || minishell->buffer[i] == '\t') && (minishell->buffer[i]))
			i++;
		if (grap_mot(minishell, &i) == 1)
			return(0);
		if (count_quote(minishell->current) != 0)
			get_double_cot(minishell->current, token, pipex,
				count_quote(minishell->current), minishell);
		else
			get_type(minishell->current, token, pipex, minishell);
		token = token->next;
		while (minishell->buffer[i] == ' ')
			i++;
		free(minishell->current);
	}
	token = tmp;
	return (1);
}
static char *get_supos_command(char *srcs, char *find)
{
	int i;
	int len;
	char *res;

	i = 0;
	while(srcs[i])
	{
		while(srcs[i] == find[i])
			i++;
		len = i;
		while(srcs[len])
			len++;
		res = ft_calloc(sizeof(char), (len - i) + 1);
		len = 0;
		while(srcs[i])
		{
			res[len] = srcs[i];
			i++;
			len++;
		}
		res[len] = '\0';
	}
	return(res);
}


static void is_a_absolut(t_token *token, t_pipex *pipex)
{
	int i;
	char *command;
	t_token *tmp;

	i = 0;
	tmp = token;
	while(token->value)
	{
		if (token->value[0] == '/' && ft_strncmp(token->value, "/bin/", 5) == 0)
		{
			command = get_supos_command(token->value, "/bin/");
			if (search_command_for_token(pipex, command) == 0)
			{
				free(token->value);
				free(token->type);
				token->value = ft_strdup(command);
				token->type  = ft_strdup("commande");
			}
			free(command);
			command = NULL;
		}
		token = token->next;
	}
	token = tmp;
}

int	tokenisation(t_token *token, t_minishell *minishell, t_pipex *pipex)
{
	minishell->flag = 0;
	pipex->path = pipex->ev;

    if (minishell->buffer == NULL || minishell->buffer[0] == '\0')
    {
        ft_putstr_fd("Input is empty\n", 2);
        return (0);
    }
	if (creat_lst(token, minishell, pipex) == 0)
		return (0);
	put_in(token, minishell);
	is_a_absolut(token, pipex);
	minishell->flag = 0;
	return (1);
}




//  regarde les cote ex: echo po"ol" fait attentoin a ne pas sauter des case a verifier dasn la fonction "grap_mot"
//il y a surement un saut de trop avce les commande et le pipe comme ca "ls "srcs" | pwd" 
