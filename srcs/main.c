/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizi <zizi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:39 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/25 14:36:55 by zizi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int var_g = 0;

int main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	t_pipex pipex;
	t_token *token;
	t_minishell minishell;

	token = ft_calloc(sizeof(t_token), 1);
	pipex.ev = ev;
	creat_the_prompt(ev, &pipex, token, &minishell);
	return (EXIT_SUCCESS);
}

