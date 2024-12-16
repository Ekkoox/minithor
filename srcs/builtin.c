/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:47:16 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/13 16:55:18 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_minishell *minishell, t_token *token)
{
    t_token *head;

    head = token;
    if (ft_strncmp(token->value, "echo", 4) == 0)
		ft_echo(token);
	else if (ft_strncmp(token->value, "cd", 2) == 0)
		ft_cd(token, minishell->env);
	else if (ft_strncmp(token->value, "pwd", 3) == 0)
		ft_pwd(token);
	else if (ft_strncmp(token->value, "env", 3) == 0)
		ft_env(minishell);
    while(token->next)
	{
		if (ft_strcmp(token->type, "heredoc") == 0)
		{
			heredoc(token, &head);
			break;
		}
		token = token->next;
	}
    token = head;
    return (EXIT_SUCCESS);
}
