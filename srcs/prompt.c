/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/18 19:51:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	error_prompt(char *buffer, ssize_t bytes_read)
{
	if (!buffer)
	{
		perror("Error calloc");
		exit(EXIT_FAILURE);
	}
	if (bytes_read < 0)
	{
		perror("Error reading input");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	exit_prompt(char *buffer)
{
	if (ft_strcmp(buffer, "exit") == 0)
	{
		ft_putstr_fd("Bisous mon chou <3\n", 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

// int	creat_the_prompt(int ac, char **av, char **ev, t_pipex *pipex, t_token *token, t_minishell *minishell, t_historique *historique)
// static void is_buiting(t_token *token)
// {
// 	if (ft_strncmp(token->value, "echo", 4) == 0)
// 		ft_echo(token);
// 	else if (ft_strncmp(token->value, "cd", 2) == 0)
// 		ft_cd(token);
// 	else if (ft_strncmp(token->value, "pwd", 3) == 0)
// 		ft_pwd(token);
// 	else if (ft_strncmp(token->value, "env", 3) == 0)
// 		ft_env(token);
// }

// static char *join_ev(char **ev)
// {
// 	char *env;
// 	int j;
// 	int i;

// 	i = 0;
// 	j = 0;
// 	while(ev[i])
// 	{
// 		env = ft_strjoin(env, ev[i]);
// 		while(env[j])
// 			j++;
// 		env[j] = ' ';
// 		i++;
// 	}
// 	env[j] = '\0';
// 	return (env);
// }

static t_env	*creat_env_list(char **ev, t_minishell *minishell)
{
	int i;
	char **split_env;
	t_env *env = minishell->env;
	t_env *tmp;

	i = 0;
	env = ft_calloc(sizeof(t_env), 1);
	tmp = env;
	while(ev[i])
	{
		split_env = ft_split_env(ev[i], '=');
		env->type = ft_calloc(sizeof(char), ft_strlen(split_env[0]));
		env->type = ft_calloc(sizeof(char), ft_strlen(split_env[1]));
		env->type = split_env[0];
		env->value = split_env[1];
		env->next = ft_calloc(sizeof(t_env), 1);
		env = env->next;
		i++;
	}
	env = tmp;
	return (env);
}

int	creat_the_prompt(char **ev, t_pipex *pipex, t_token *token, t_minishell *minishell)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 0;	
	buffer = (char *)ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		error_prompt(buffer, bytes_read);
	minishell->env = creat_env_list(ev, minishell);
	while(1)
	{
		buffer = readline(">");
		if (!buffer)
			return (EXIT_FAILURE);
		bytes_read = ft_strlen(buffer);
		buffer[bytes_read] = '\0';
		// if (bytes_read > 0 && buffer[bytes_read - 1] == '\n')
		// 	buffer[bytes_read - 1] = '\0';
		if (exit_prompt(buffer) == 0)
			break ;
		minishell->buffer = buffer;
		add_history(buffer);
		tokenisation(token, minishell, pipex);
		check_token(token, minishell->env);
		pipex->command_1 = token->value;
		if (bytes_read > 0)
		{
			if (ft_strncmp(token->value, "echo", 4) == 0)
				ft_echo(token);
			else if (ft_strncmp(token->value, "cd", 2) == 0)
				ft_cd(token, minishell->env);
			else if (ft_strncmp(token->value, "pwd", 3) == 0)
				ft_pwd(token);
			else if (ft_strncmp(token->value, "env", 3) == 0)
		 		ft_env(minishell);
			else
				army_of_fork(ev, pipex, minishell);
		}
	}
	if (bytes_read < 0)
		error_prompt(buffer, bytes_read);
	free(buffer);
	return (EXIT_SUCCESS);
}


//
