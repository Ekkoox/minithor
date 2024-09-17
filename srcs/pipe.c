/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/17 20:02:51 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_the_pipe(t_pipex *pipex)
{
	if (pipe(pipex->fd) == -1)
	{
		perror("Error pipe\n");
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
}
static void	error_execve(t_pipex *pipex)
{
	ft_putstr_fd("Execve error\n", 2);
	free_all(pipex);
	exit(EXIT_FAILURE);
}

static void	first_child(t_pipex *pipex)
{
	int		fd;
	char	*path;

	fd = open(pipex->file_1, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Permission denied\n", 2);
		return ;
	}
	if (dup2(fd, 0) == -1)
		return ;
	if (dup2(pipex->fd[1], 1) == -1)
		return ;
	close(fd);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	path = get_the_command(pipex);
	if (!path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	if (execve(path, pipex->command_1, pipex->ev) == -1)
		error_execve(pipex);
}

void	army_of_fork(int ac, char **av, char **ev, t_pipex *pipex)
{
	int	id_fork;

	find_the_path(ac, av, ev, pipex);
	split_the_path(pipex);	
	create_the_pipe(pipex);
	id_fork = fork();
	if (id_fork == -1)
	{
		ft_printf("Error with the fork\n");
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	if (id_fork == 0)
		first_child(pipex);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}
