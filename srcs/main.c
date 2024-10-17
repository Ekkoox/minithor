/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:39 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/27 18:56:42 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **ev)
{
	t_pipex pipex;
	t_token *token;
	t_minishell minishell;

	if (ac != 1)
		return (ft_putstr_fd("Error number of arguments\n", 2), EXIT_FAILURE);
	
	token = ft_calloc(sizeof(t_token), 1);
	pipex.ev = ev;
	creat_the_prompt(ac, av, ev, &pipex, token, &minishell);
	return (EXIT_SUCCESS);
}

