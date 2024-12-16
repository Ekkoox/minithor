/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/16 16:28:52 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */



#include "minishell.h"

int	error_prompt(char *buffer, ssize_t bytes_read)
{
	if (!buffer)
	{
		perror("Error calloc");
		exit(EXIT_FAILURE);
	}
	if (bytes_read < 0)
	{
		perror("Error reading input");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exit_prompt(char *buffer)
{
	if (ft_strcmp(buffer, "exit") == 0)
	{
		ft_putstr_fd("Bisous mon chou <3\n", 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static void free_env_list(t_env *env) 
{
    t_env *tmp;

    while (env) 
	{
        tmp = env->next;
        free(env->type);
        free(env->value);
        free(env);
        env = tmp;
    }
}

static t_env	*creat_env_list(char **ev, t_minishell *minishell)
{
	int i;
	char **split_env;
	t_env *env = minishell->env;
	t_env *tmp;

	i = 0;
	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	tmp = env;
	while(ev[i])
	{
		split_env = ft_split_env(ev[i], '=');
		env->type = ft_calloc(sizeof(char), ft_strlen(split_env[0]));
		if (!env->type)
			return (NULL);
		env->type = ft_calloc(sizeof(char), ft_strlen(split_env[1]));
		if (!env->type)
			return (NULL);
		env->type = split_env[0];
		env->value = split_env[1];
		env->next = ft_calloc(sizeof(t_env), 1);
		if (!env->next)
			return (NULL);
		env = env->next;
		i++;
	}
	env = tmp;
	return (env);
}

void handle_sigint(int sig)
{
    (void)sig;

    rl_replace_line("", 0);
    rl_on_new_line();
	ft_printf("\n");
    rl_redisplay();
}

static int count_heredoc(t_token *token)
{
	int i;

	i  = 0;
	while(token->next)
	{
		if (ft_strcmp(token->type, "heredoc") == 0)
			i++;
		token = token->next;
	}
	return (i);
}

int	creat_the_prompt(char **ev, t_pipex *pipex, t_token *token, t_minishell *minishell)
{
	char	*buffer;
	ssize_t	bytes_read;
	int nb_heredoc;

	bytes_read = 0;	
	minishell->env = creat_env_list(ev, minishell);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while(1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			ft_printf("exit\n");
			return (EXIT_FAILURE);
		}
		bytes_read = ft_strlen(buffer);
		buffer[bytes_read] = '\0';
		if (exit_prompt(buffer) == 0)
			break ;
		minishell->buffer = buffer;
		add_history(buffer);
		tokenisation(token, minishell, pipex);
		pipex->command_1 = token->value;
		if (bytes_read > 0)
		{
			if (is_builtin(minishell, token) != 0)
				army_of_fork(ev, pipex, minishell, token);
		}
		free(buffer);
	}
	if (bytes_read < 0)
		error_prompt(buffer, bytes_read);
	free_env_list(minishell->env);
	return (EXIT_SUCCESS);
}



//a tester
//cote double cote ("") ('')
//heredoc genre double heredoc
//export en mode bien mechant



//gere le cas avec les expand commande genre
//export cmd="ls"
//suffi de bien tout fusioner comme il faut
