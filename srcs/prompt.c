/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/28 18:25:45 by roane            ###   ########.fr       */
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
		env->type = ft_strdup(split_env[0]);
		env->value = ft_strdup(split_env[1]);
		if (!env->type || !env->value)
			return (NULL);
		env->next = ft_calloc(sizeof(t_env), 1);
		if (!env->next)
			return (NULL);
		env = env->next;
		i++;
        free(split_env[0]);
        free(split_env[1]);
        free(split_env);
	}
	env = tmp;
	return (env);
}

int     count_size_lst(t_env *env)
{
    int i;

    i = 0;
    while (env)
    {
        env = env->next;
        i++;
    }
    return (i);
}

int    creat_the_prompt(char **ev, t_pipex *pipex, t_token *token, t_minishell *minishell)
{
    char    *buffer;
    t_token *head;
    int flag; 
    int nb_heredoc;
	ssize_t	bytes_read;

    flag = 0;
    bytes_read = 0;    
    head = token;
    minishell->env = creat_env_list(ev, minishell);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_sigint);
    if (count_size_lst(minishell->env) > 6)
        pipex->flag = 1;
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
        flag = tokenisation(token, minishell, pipex);
        if (flag == EXIT_FAILURE)
            continue;
        if (check_token(token, minishell->env, pipex) == 0)
        { 
        //     while(token->next)
        //     {
        //         ft_printf("le type: %s. de la valeur de:  %s\n", token->type, token->value);
        //         if (ft_strcmp(token->type, "commande") == 0)
        //             ft_printf("index %d\n", token->index);
        //         token = token->next;
        //    }
        //     token = head;
            nb_heredoc = count_heredoc(token);
            pipex->command_1 = token->value;
            if (bytes_read > 0)
            {
                while(nb_heredoc)
                {
                    if (ft_strcmp(token->type, "heredoc") == 0)
                        if (heredoc(token, &head, &nb_heredoc, minishell, pipex) == 1)
                            break;
                    token = token->next;
                }
                token = head;
                if (is_builtin(minishell, token) == 0)
                    if(ft_strcmp(token->type, "heredoc") != 0)
                        army_of_fork(ev, pipex, minishell, token);
            }
        }
        token = head;
        if (ft_strcmp(token->type, "heredoc") != 0)
            mini_free(minishell, pipex, token, 1);
    }
    free_env_list(minishell->env);
    free_tok_list(token, 0);
    if (bytes_read < 0)
        error_prompt(buffer, bytes_read);
    return (EXIT_SUCCESS);
}

