/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/27 19:12:26 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_execve(t_pipex *pipex)
{
	ft_putstr_fd("Execve error\n", 2);
	free_all(pipex);
	// exit(EXIT_FAILURE);
}

static void	first_child(t_pipex *pipex, t_token *token)
{
	char	*path;
	char **split;
	// int fd;

	split = ft_split(token->value, '0');
	// fd = open(pipex->file_1, O_RDONLY);
	// if (fd == -1)
	// {
	// 	ft_putstr_fd("Permission denied\n", 2);
	// 	return ;
	// }
	// close(fd);
	path = get_the_command(pipex);
	if (!path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		free_all(pipex);
		// exit(EXIT_FAILURE);
	}
	if (execve(path, split, pipex->ev) == -1)
		error_execve(pipex);
}

void	army_of_fork(char **ev, t_pipex *pipex, t_token *token)
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
		first_child(pipex, token);
	wait(NULL);
}
