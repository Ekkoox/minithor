/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:39 by enschnei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/04 13:59:16 by razouani         ###   ########.fr       */
=======
/*   Updated: 2024/11/04 16:58:06 by enschnei         ###   ########.fr       */
>>>>>>> Enzo
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **ev)
{
	t_pipex pipex;
	t_token *token;
	t_minishell minishell;
	t_historique *historique;

	if (ac != 1)
		return (ft_putstr_fd("Error number of arguments\n", 2), EXIT_FAILURE);
	token = ft_calloc(sizeof(t_token), 1);
	historique = ft_calloc(sizeof(t_historique), 1);
	pipex.ev = ev;
	creat_the_prompt(ac, av, ev, &pipex, token, &minishell, historique);
	return (EXIT_SUCCESS);
}

