/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:59:59 by razouani          #+#    #+#             */
/*   Updated: 2024/09/24 19:02:00 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	creat_node(char *type, t_token *token, char *value)
{
	token->type = ft_strdup(type);
	token->value = ft_strdup(value);
	token->next = ft_calloc(sizeof(t_token), 1);
	token = token->next;
}

static int grap_mot(t_minishell *minishell, int index)
{
	int i;
	int len;
	int j;

	i = index;
	j = 0;
	while(minishell->buffer[i] != ' ' && minishell->buffer[i] != '\t' && minishell->buffer[i])
		i++;
	len = i - index;
	if (len <= 0)
		return (0);
	minishell->current = ft_calloc(sizeof(char), len + 1);
	while (index < i && minishell->buffer[index])
	{
		minishell->current[j] = minishell->buffer[index];
		j++;
		index++;
	}
	minishell->current[index] = '\0';
	return(index);
}

static int search_the_command(char *commande, t_pipex *pipex)
{
	char *path;
	
	if (!ft_strchr(commande, '/') && commande[0] != '.')
	{
		path = search_the_path(pipex, commande);
		if (!path)
		{
			ft_putstr_fd("Command not found\n", 2);
			return(1);
		}
	}
	return(0);
}


static void	get_type(char *mot, t_token *token, t_pipex *pipex)
{
	if (chdir(mot) == 0)
		creat_node("dossier", token, mot);
	else if (search_the_command(mot, pipex) == 0)
		creat_node("commande", token, mot);
	else if (ft_strcmp(mot, ">") == 0)
		creat_node("redirect output", token, mot);
	else if (ft_strcmp(mot, "<") == 0)
		creat_node("redirect input", token, mot);
	
}

static char *dans_cot(char *buffer, int *index)
{
	int i;
	char *mot;
	int y;
	
	i = *index;
	y = 0;
	while(buffer[*index] && buffer[*index] != '"')
	{
		if (buffer[i] == '\0')
			return (NULL);
		i++;
	}
	mot = ft_calloc(sizeof(char), i - *index + 1);
	while(index < i)
	{
		mot[y] = buffer[*index];
		y++;
		index++;
	}
	return(mot);
}

static void get_double_cot(char *buffer, int *index, t_token *token)
{
	int i;
	char *mot;
	int y;
	
	i = *index;
	y = 0;
	while(buffer[*index] && buffer[*index] != '"')
	{
		if (buffer[i] == '\0')
			return (0);
		i++;
	}
	mot = ft_calloc(sizeof(char), i - *index + 1);
	while(index < i)
	{
		mot[y] = buffer[*index];
		y++;
		index++;
	}
	
	/*
		fait ne sorte que la fonction comprenne le cas "l"s"" utilise la fonctione juste au dessus
	*/
}


int	tokenisation(t_token *token, t_minishell *minishell, t_pipex *pipex)
{
	int i;
	//t_token *tmp = token;
	// int y = 0;
	pipex->path = pipex->ev;
	
	i = 0;
	while(minishell->buffer[i])
	{
		while((minishell->buffer[i] == ' ' || minishell->buffer[i] == '\t') && (minishell->buffer[i]))
			i++;
		if (minishell->buffer[i] == '"')
			i = get_double_cot(minishell->buffer, &i, token);
		i = grap_mot(minishell, i);
		get_type(minishell->current, token, pipex);
		ft_printf("le type: %s\n", token->type);
		ft_printf("le value: %s\n", token->value);
	}
	return (EXIT_SUCCESS);	
}


//ESSAYE DE FAIRE UNE FONCTION QUI VERIFIE SI LE PATH EST EST BON POUR VOIR SI C'EST UNE COMMANDE OU PAS

