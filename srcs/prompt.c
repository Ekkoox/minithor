/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2025/03/19 22:11:49 by roane            ###   ########.fr       */
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

static void init_env(t_minishell *minishell, char **ev, int *index)
{
    	char **split_env;


        split_env = ft_split_env(ev[*index], '=');
		minishell->env->type = ft_strdup(split_env[0]);
		minishell->env->value = ft_strdup(split_env[1]);
		if (!minishell->env->type || !minishell->env->value)
			return;
		minishell->env->next = ft_calloc(sizeof(t_env), 1);
		if (!minishell->env->next)
			return;
		minishell->env = minishell->env->next;
		*index += 1;
        free(split_env[0]);
        free(split_env[1]);
        free(split_env); 
}

static void	    creat_env_list(char **ev, t_minishell *minishell)
{
	int i;
	t_env *tmp;

	i = 0;
	minishell->env = ft_calloc(sizeof(t_env), 1);
	if (!minishell->env)
		return;
	tmp = minishell->env;
	while(ev[i])
        init_env(minishell, ev, &i);
	minishell->env = tmp;
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

void free_list(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->value);
        free(tmp);
    }
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
    creat_env_list(ev, minishell);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_sigint);
    if (count_size_lst(minishell->env) > 6)
        pipex->flag = 1;
    while(1)
    {
        buffer = readline(">");
        if (!buffer)
        {
            free(token);
            free_env_list(minishell);
            ft_printf("exit\n");
            return (EXIT_FAILURE);
        }
        bytes_read = ft_strlen(buffer);
        buffer[bytes_read] = '\0';
        minishell->buffer = buffer;
        add_history(buffer);
        flag = tokenisation(token, minishell, pipex);
        if (flag == 0)
            continue;
        if (check_token(token, minishell->env, pipex) == 0)
        {
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
        if (ft_strcmp(token->type, "heredoc") == 0)
            mini_free(minishell, pipex, token, 0);
        else 
            mini_free(minishell, pipex, token, 1);
    }
    free_env_list(minishell);
    free_tok_list(token, 0);
    if (bytes_read < 0)
        error_prompt(buffer, bytes_read);
    return (EXIT_SUCCESS);
}
