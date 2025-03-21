/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:41:58 by enschnei          #+#    #+#             */
/*   Updated: 2025/03/19 23:25:06 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int ft_strlen_V2(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	free(str);
	str = NULL;
	return(i);
}

static int  count_sign(char *value)
{
	int i;
	int sign;

	i = 0;
	sign = 0;
	if (value == NULL)
		return (0);	
	while(value[i])
	{
		if (value[i] == '$')
			sign++;
		i++;
	}
	return (sign);
}

static void ajust_value(t_env *env, t_token *token, int *i, int *j)
{
	while(env->value[*j])
	{
		token->value[*i] = env->value[*j];
		*i = *i + 1;
		*j = *j + 1;
	}
}

static void dup_value_expand(char *dup_value, t_token *token, t_env *env, int index)
{
	int i;
	int y;
	int j;

	y = 0;
	i = 0;
	j = 0;
	while(dup_value[y])
	{
		if (dup_value[y] == '$')
		{
			ajust_value(env, token, &i, &j);
			while(y < index)
				y++;
		}
		token->value[i] = dup_value[y];
		if (!dup_value[y])
			break;
		i++;
		y++;
	}
	token->value[i] = '\0';
	free(dup_value);
}

static void	expand_plus(t_token *token, t_env *env, int index, char *expand)
{
	int len;
	char *dup_value;

	while(env->next && (ft_strcmp(env->type, expand)))//a voir si on veut afficher la toute dernier variable
		env = env->next;
	len = (ft_strlen(token->value) - (ft_strlen_V2(expand) + 1) + ft_strlen(env->value));
	dup_value = ft_strdup(token->value);
	free(token->value);
	token->value = ft_calloc(sizeof(char), len + 1);
	if(token->value == NULL)
		return;
	dup_value_expand(dup_value, token, env, index);
}


static int find_on_env(t_token *token, int index, t_env *env)
{
	char *sup_exp;
	int i;
	int j;

	i = index;
	j = 0;
	while((token->value[i]) && (token->value[i] != ' ' && token->value[i] != '$'))
		i++;
	sup_exp = ft_calloc(sizeof(char), ((i - index) + 1));
	if (!sup_exp)
		return (0);
	while(index < i)
	{
		sup_exp[j] = token->value[index];
		index++;
		j++;
	}
	while(env->next)
	{
		if (ft_strcmp(sup_exp, env->type) == 0)
			return(ft_strlen_V2(sup_exp));
		env = env->next;
	}
	return(free(sup_exp), 0);	
}

static void get_line(t_token *token)
{
	int i;
	char *str;
	int j;

	i = 0;
	j = 0;
	while(token->value[i] && token->value[i] != '$')
		i++;
	str = ft_calloc(sizeof(char), i + 1);
	while(j < i)
	{
		str[j] = token->value[j];
		j++;
	}
	free(token->value);
	token->value = ft_strdup(str);
}

static void	expand_env(t_token *token, t_env *env, int *index)
{
	char *expand;
	int i;
	int len;
	t_env *tmp;

	i = 0;
	tmp = env;
	len = find_on_env(token, *index, env);
	env = tmp;
	if(len == 0)
	{
		get_line(token);
		return;
	}
	expand = ft_calloc(sizeof(char), len + 1);
	while(token->value[*index] != ' '  && token->value[*index] && token->value[*index] != '$')
	{
		expand[i] = token->value[*index];
		i++;
		*index = *index + 1;
	}
	expand[i] = '\0';
	i = *index;
	expand_plus(token, env, i, expand);
}


static void check_file(char *file, char *chevron, t_token *token, t_pipex *pipex)
{
	if (ft_strcmp(chevron, ">") == 0)
		pipex->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(chevron, "<") == 0)
		pipex->fd = open(file, O_RDONLY, 0644);
	else
		pipex->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(token->next->type);
	token->next->type = ft_strdup("file");
	if (!token->next->type)
		return ;
	if (pipex->fd == -1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n	", 2);
		g_var = 2;
		return ;
	}	
}

static void duplicate_value(t_token *token, int index, int j, char *dup_value)
{
	while(dup_value[index])
	{
		token->value[j] = dup_value[index];
		index++;
		j++;
	}
	token->value[j] = '\0';
}

static void swap_plan(t_token *token, int index, int start)
{
	int i;
	int len;
	int j;
	char *dup_value;

	i = (index - start);
	j = 0; 
	len = start;
	dup_value = ft_strdup(token->value);
	if (!dup_value)
		return ;
	len = (ft_strlen(token->value) - i);
	free(token->value);
	token->value = ft_calloc(sizeof(char), len + 1);
	if (!token->value)
		return ;
	while(j < start)
	{
		token->value[j] = dup_value[j];
		j++;
	}
	duplicate_value(token, index, j, dup_value);
	free(dup_value);
}

static int juge_expand(t_token *token, int *index, t_env *env, int *nb_sign)
{
	int i;
	int j;
	char *expand;
	t_env *tmp;

	i = *index + 1;
	j = 0;
	tmp = env;
	while(token->value[i] && (token->value[i] != ' ' && token->value[i] != '$'))
		i++;
	if (i == *index + 1)
		return (0);
	expand = ft_calloc(sizeof(char), i + 1);
	if (!expand)
		return (EXIT_FAILURE);
	i = *index + 1;
	while(token->value[i] && (token->value[i] != ' ' && token->value[i] != '$'))
	{
		expand[j] = token->value[i];
		i++;
		j++;
	}
	while(env->next)
	{
		if (ft_strcmp(expand, env->type) == 0)
			return(free(expand), 1);
		env = env->next;
	}
	*nb_sign = *nb_sign - 1;
	env = tmp;
	return (free(expand), swap_plan(token, i, *index), 0);
}

static void check_dollar(t_token *token, t_env *env)
{
	int i;
	int nb_sign;

	i = 0;
	nb_sign = count_sign(token->value);
	while(token->value[i] && nb_sign > 0 && ft_strlen(token->value) > 1)
	{	
		if (token->value[i] == '$' && token->value[i + 1] == '?')
		{
			free(token->value);
			token->value = ft_itoa(g_var);
			i++;
			break;
		}
		if(token->value[i] == '$' && juge_expand(token, &i, env, &nb_sign))
		{
			i++;
			expand_env(token, env, &i);
			nb_sign--;
		}
		if(token->value[i] != '$' && token->value[i])
			i++;
	}
}

int		check_token(t_token *token, t_env *env, t_pipex *pipex)
{
	t_token *check;
	int index_command;
	t_token *tmp;

	index_command = 1;
	tmp = token;
	while(token->next)
	{
		if (ft_strcmp(token->type, "commande") == 0)
			token->index = index_command++;
		check_dollar(token, env);
		if (((ft_strcmp(token->type, "redirect output") == 0) || (ft_strcmp(token->type, "redirect input") == 0)) && (token->next->type))
			check_file(token->next->value, token->value, token, pipex);
		check = token;
		token = token->next;
	}
	if (ft_strcmp(check->type, "pipe") == 0)
		return(token = tmp, 1);
	if (ft_strcmp(check->type, "redirect output") == 0 || ft_strcmp(check->type, "redirect input") == 0)
		return(ft_printf("syntax error near unexpected token `newline'\n"), 1);
	 return (token=tmp, 0);
}
