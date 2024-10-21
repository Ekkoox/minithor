/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2024/10/21 18:02:18 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_execve(t_pipex *pipex)
{
	ft_putstr_fd("Execve error\n", 2);
	free_all(pipex);
	// exit(EXIT_FAILURE);
}

static void	first_child(t_pipex *pipex, t_minishell *minishell)
{
	char	*path;
	//char **split;
	int y = 0;
	while(minishell->command_exac[y])
	{
		ft_printf("%s\n", minishell->command_exac[y]);
		y++;
	}

	//split = ft_split(pipex->command_1, '0');
	path = get_the_command(pipex);
	if (!path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		free_all(pipex);
		// exit(EXIT_FAILURE);
	}
	if (execve(path, minishell->command_exac, pipex->ev) == -1)
		error_execve(pipex);
}

void	army_of_fork(int ac, char *av, char **ev, t_pipex *pipex, t_minishell *minishell)
{
	int	id_fork;

	find_the_path(ev, pipex);
	split_the_path(pipex);
	id_fork = fork();
	if (id_fork == -1)
	{
		ft_printf("Error with the fork\n");
		free_all(pipex);
		// exit(EXIT_FAILURE);
	}
	if (id_fork == 0)
		first_child(pipex, minishell);
	wait(NULL);
}
