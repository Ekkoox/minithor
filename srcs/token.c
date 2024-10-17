/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:59:59 by razouani          #+#    #+#             */
/*   Updated: 2024/09/30 17:59:54 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	creat_node(char *type, t_token *token, char *value)
{
	token->type = ft_strdup(type);
	token->value = ft_strdup(value);
	token->next = ft_calloc(sizeof(t_token), 1);
}

static void grap_mot(t_minishell *minishell, int *index)
{
	int i;
	int len;
	int j;

	i = *index;
	j = 0;
	while(minishell->buffer[i] != ' ' && minishell->buffer[i] != '\t' && minishell->buffer[i])
		i++;
	len = i - *index;
	if (len <= 0)
		return;
	minishell->current = ft_calloc(sizeof(char), len + 1);
	while (*index < i && minishell->buffer[*index])
	{
		minishell->current[j] = minishell->buffer[*index];
		j++;
		*index += 1;
	}
	minishell->current[*index] = '\0';
	return;
}



static int	get_type(char *mot, t_token *token, t_pipex *pipex)
{
	int fd;

	fd = 0;
	fd = open(mot, fd); // c'est de la merde
	if (chdir(mot) == 0)
		return (creat_node("dossier", token, mot), 0);
	else if (fd > 0)
		return (creat_node("file", token, mot), 0);
	else if (search_command_for_token(pipex, mot) == 0)
		return (creat_node("command", token, mot), 0);
	else if (ft_strcmp(mot, ">") == 0)
		return (creat_node("redirect output", token, mot), 0);
	else if (ft_strcmp(mot, "<") == 0)
		return (creat_node("redirect input", token, mot), 0);
	return (1);
}


static int count_chef(char *mot)
{
	int i;
	int c;
	char chef;

	i = 0;
	c = 0;
	while(mot[i])
	{
		if ((mot[i] == 34 || mot[i] == 39) && (c == 0))
			chef = mot[i];
		if (mot[i] == chef)
			c++;
		i++;
	}
	return (c);
}

// static char *dans_cot(char *buffer, int *index, char chef)
// {
// 	int i;
// 	char *mot;
// 	int y;
	
// 	i = *index + 1;
// 	y = 0;
// 	while (buffer[i] && buffer[i + 1] != chef)
// 	{
// 		if (buffer[i] == '\0')
// 			return (NULL);
// 		i++;
// 	}
// 	mot = ft_calloc(sizeof(char), (i - *index) + 1);
// 	while(*index < i)
// 	{
// 		*index += 1;
// 		mot[y] = buffer[*index];
// 		y++;
// 	}
// 	mot[y] = '\0';
// 	return(mot);
// }

static void get_double_cot(char *mot, int *index, t_token *token, t_pipex *pipex, int chef)
{
	(void)chef;
	int i;
	//char *mot;
	int y;
	int c;
	
	i = *index;
	y = 0;
	c = 0;
	//mot = dans_cot(buffer, index, chef);
	// ft_printf("enzo le pute: ||%s||\n", mot);
	while(mot[y])
	{
		if (mot[y] == ' ')
			c++;
		y++;
	}
	if(c == 0)
	{
		if (get_type(mot, token, pipex) == 0)
			return;
		else
			creat_node("string", token, mot);
	}
}


int	tokenisation(t_token *token, t_minishell *minishell, t_pipex *pipex)
{
	int i;
	// int y = 0;
	
	i = 0;
	while(minishell->buffer[i])
	{
		while((minishell->buffer[i] == ' ' || minishell->buffer[i] == '\t') && (minishell->buffer[i]))
			i++;
		grap_mot(minishell, &i);
		if (count_chef(minishell->current) != 0)
			get_double_cot(minishell->current, &i, token, pipex, count_chef(minishell->current));
		get_type(minishell->current, token, pipex);
		ft_printf("le type: %s\n", token->type);
		ft_printf("le value: %s\n", token->value);
		token = token->next;	
	}
	return (EXIT_SUCCESS);
}

// faire un enum pour differencier les types au lieu des strings (plus maintenable et opti)
// ne pas verifier si un argument est un fichier si c'est pas une redirection
// convertir la liste chainee en tableaux pour l'envoyer a execve