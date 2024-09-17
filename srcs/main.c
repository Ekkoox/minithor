/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:39 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/17 17:06:34 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **ev)
{
	(void) av;
	(void) ev;

	if (ac != 1)
		return (ft_putstr_fd("Error number of arguments\n", 2), EXIT_FAILURE);
	creat_the_prompt();
	return (EXIT_SUCCESS);
}

