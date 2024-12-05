/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/05 15:21:59 by enschnei         ###   ########.fr       */
/*                                                                            */
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

    //rl_replace_line("", 0);
    rl_on_new_line();
	ft_printf("\n");
    rl_redisplay();
}

int	creat_the_prompt(char **ev, t_pipex *pipex, t_token *token, t_minishell *minishell)
{
	char	*buffer;
	ssize_t	bytes_read;

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
		// check_token(token, minishell->env);
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
			t_token *tmp = token;
			while(tmp->value)
			{
				if (ft_strcmp(tmp->value, "<<") == 0)
					heredoc(tmp);
				tmp = tmp->next;
			}
			// else
			army_of_fork(ev, pipex, minishell, token);
		}
		free(buffer);
	}
	if (bytes_read < 0)
		error_prompt(buffer, bytes_read);
	free_env_list(minishell->env);
	return (EXIT_SUCCESS);
}
