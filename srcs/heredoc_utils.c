/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:30 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/30 18:16:04 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int sig)
{
	(void)sig;
	close(0);
	ft_printf("\n");
	exit(EXIT_FAILURE);
}

int	execut_heredoc(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!(ft_strcmp(token->type, "heredoc") == 0) || (token->next->type))
	{
		token = tmp;
		return (1);
	}
	token = tmp;
	return (0);
}
