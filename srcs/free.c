/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:36:02 by razouani          #+#    #+#             */
/*   Updated: 2024/12/19 17:39:46 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_tab_int(int **tab, int num_cmds)
{
    int i;

    i = 0;
    while(i < num_cmds - 1)
    {
        free(tab[i]);
        tab[i] = NULL;
        i++;
    }
    free(tab);
    tab = NULL;
}

void free_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i])
    {
        free(tab[i]);
        tab[i] = NULL;
        i++;
    }
    free(tab);
    tab = NULL;
}

void repos_army(t_pipex *pipex, char **command)
{
    if (command)
        free_tab(command);
    if (pipex->pipes)
        free_tab_int(pipex->pipes, pipex->num_cmds);
}

// void free_tok(t_token *token, t_minishell *minishell, t_pipex *pipex)
// {
//     (void)*token;
//     // if (pipex->command_1)
//     //     free_tab(pipex->command_1);
//     if (pipex->path)
//         free_tab(pipex->path);
//     if (minishell->current)
//         free(minishell->current);
// }

void free_env_list(t_env *env) 
{
    t_env *target;

    while (env)
	{
        target = env;
        env = env->next;
        free(target->type);
        free(target->value);
        target->type = NULL;
        target->value = NULL;
        free(target);
        target = NULL;
    }
}

void    free_tok_list(t_token *token)
{
    t_token *target;
    int i = 0;
    
    while(token)
    {
        ft_printf("%d\n", i);
        target = token;
        token = token->next;
        if (target->type)
            free(target->type);
        if (target->value)
            free(target->value);
        target->type = NULL;
        target->value = NULL;
        free(target);
        target = NULL;
        i++;
    }
}

void    free_minishell_list(t_minishell *minishell)
{
    if (minishell->buffer)
        free(minishell->buffer);
    if (minishell->current)
        free(minishell->current);
    // if (minishell->pid)
    //     free(minishell->pid);
}

void mini_free(t_minishell *minishell, t_pipex *pipex)
{
    //free_tok_list(minishell->token);
    free(minishell->buffer);
    minishell->buffer = NULL;
    free(minishell->current);
    minishell->current = NULL;
    free_tab(minishell->command_exac);
    free_tab(pipex->path);
}