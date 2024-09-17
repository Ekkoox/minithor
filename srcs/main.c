/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:39 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/17 20:07:24 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **ev)
{
	t_pipex pipex;

	if (ac != 1)
		return (ft_putstr_fd("Error number of arguments\n", 2), EXIT_FAILURE);
	creat_the_prompt(ac, av, ev, &pipex);
	return (EXIT_SUCCESS);
}

