/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/08 16:10:48 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	error_execve(t_pipex *pipex)
// {
// 	ft_putstr_fd("Execve error\n", 2);
// 	free_all(pipex);
// 	// exit(EXIT_FAILURE);
// }

// static void	first_child(t_pipex *pipex, t_minishell *minishell)
// {
// 	char	*path;
// 	char 	*buffer;

// 	buffer = NULL;
// 	path = get_the_command(pipex);
// 	if (!path)
// 	{
// 		ft_putstr_fd("No such file or directory\n", 2);
// 		free_all(pipex);
// 		// exit(EXIT_FAILURE);
// 	}
// 	if (execve(path, minishell->command_exac, pipex->ev) == -1)
// 		error_execve(pipex);
// }

// void	army_of_fork(char **ev, t_pipex *pipex, t_minishell *minishell)
// {
// 	int	id_fork;

// 	find_the_path(ev, pipex);
// 	split_the_path(pipex);
// 	id_fork = fork();
// 	if (id_fork == -1)
// 	{
// 		ft_printf("Error with the fork\n");
// 		free_all(pipex);
// 		// exit(EXIT_FAILURE);
// 	}
// 	if (id_fork == 0)
// 		first_child(pipex, minishell);
// 	wait(NULL);
// }

static void error_execve(t_pipex *pipex)
{
	ft_putstr_fd("Execve error\n", 2);
	free_all(pipex);
	exit(EXIT_FAILURE);
}

static void execute_command(t_pipex *pipex, t_minishell *minishell, int cmd_index)
{
	char *path;
	int i;

	path = get_the_command(pipex);
	if (!path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	// if (cmd_index > 0)
	// 	dup2(pipex->pipes[cmd_index - 1][0], STDIN_FILENO);
	// if (cmd_index < pipex->num_cmds - 1)
	// 	dup2(pipex->pipes[cmd_index][1], STDOUT_FILENO);
	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	if (execve(path, minishell->command_exac + cmd_index, pipex->ev) == -1)
		error_execve(pipex);
}

void army_of_fork(char **ev, t_pipex *pipex, t_minishell *minishell)
{
	int i;
	pid_t pid;

	find_the_path(ev, pipex);
	split_the_path(pipex);
	pipex->num_cmds = 3;
	pipex->pipes = malloc(sizeof(int *) * (pipex->num_cmds - 1));

	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipex->pipes[i]) == -1)
		{
			perror("Pipe creation failed");
			free_all(pipex);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < pipex->num_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			free_all(pipex);
			exit(EXIT_FAILURE);
		}
		ft_printf("%s\n", minishell->command_exac[0]);
		if (pid == 0)
			execute_command(pipex, minishell, i);
		if (i > 0)
			close(pipex->pipes[i - 1][0]);
		if (i < pipex->num_cmds - 1)
			close(pipex->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < pipex->num_cmds)
	{
		wait(NULL);
		i++;
	}
	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}
