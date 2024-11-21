/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:39 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/21 18:05:10 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	t_pipex pipex;
	t_token token;
	t_minishell minishell;

	// token = ft_calloc(sizeof(t_token), 1);
	// minishell = ft_calloc(sizeof(t_minishell), 1);
	ft_bzero(&token, sizeof(t_token));
	pipex.ev = ev;
	creat_the_prompt(ev, &pipex, &token, &minishell);
	// free(&pipex);
	// free(minishell);
	// free(token);
	return (EXIT_SUCCESS);
}

