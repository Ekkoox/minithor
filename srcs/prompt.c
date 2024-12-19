/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/19 17:38:08 by razouani         ###   ########.fr       */
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

int    creat_the_prompt(char **ev, t_pipex *pipex, t_token *token, t_minishell *minishell)
{
    char    *buffer;
    t_token *head;
    int nb_heredoc;
	ssize_t	bytes_read;

    bytes_read = 0;    
    head = token;
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
        nb_heredoc = count_heredoc(token);
        pipex->command_1 = token->value;
        if (bytes_read > 0)
        {
            while(nb_heredoc)
            {
                if (ft_strcmp(token->type, "heredoc") == 0)
                    if (heredoc(token, &head, &nb_heredoc) == 1)
                        break;
                token = token->next;
            }
            token = head;
            if (is_builtin(minishell, token) == 0)
                if(ft_strcmp(token->type, "heredoc") != 0)
            army_of_fork(ev, pipex, minishell, token);
        }
        mini_free(minishell, pipex);
        // free_tab(minishell->command_exac);
        // free(buffer);
    }
    free_env_list(minishell->env);
    free_tok_list(token);
    free_minishell_list(minishell);
    if (bytes_read < 0)
        error_prompt(buffer, bytes_read);
    return (EXIT_SUCCESS);
}



//a tester
//cote double cote ("") ('')
//heredoc genre double heredoc
//export en mode bien mechant



//gere le cas avec les expand commande genre
//export cmd="ls"
//suffi de bien tout fusioner comme il faut
