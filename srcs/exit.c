/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:57:31 by enschnei          #+#    #+#             */
/*   Updated: 2025/02/09 00:38:59 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_tokens(t_token *token)
{
    t_token *tmp;

    while (token)
    {
        tmp = token->next;
        free(token->value);
        free(token);
        token = tmp;
    }
}

int ft_exit(t_minishell *minishell, t_token *token)
{   
    free(token->type);
    free_tokens(token);
    free_tab(minishell->command_exac);
    free_env_list(minishell);
    ft_putstr_fd("Bisous mon chou <3\n", 1);
    exit(EXIT_SUCCESS);
}
