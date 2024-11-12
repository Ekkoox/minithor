/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/12 22:02:43 by enschnei         ###   ########.fr       */
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



static int count_pipe(t_token *token)
{
	t_token *tmp;
	int i;

	tmp = token;
	i = 0;
	while(token->next)
	{
		if (ft_strcmp(token->type, "pipe") == 0)
			i++;
		token = token->next;
	}
	token = tmp;
	return (i + 1);
}

static void dup_command(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while(token->next)
	{
		dup2()
		token = token->next;
	}
}
}

static void execute_command(t_pipex *pipex, int cmd_index, t_token *token, t_minishell *minishell)
{
	char *path;
	t_token *tmp;
	int i;
	int command_n;

	tmp = token;
	path = get_the_command(pipex);
	command_n = count_pipe(token);
	minishell->pid = ft_calloc(sizeof(minishell->pid), 1);
	if (!path)	
	{
		ft_putstr_fd("No such file or directory\n", 2);
		free_all(pipex);
		exit (EXIT_FAILURE);
	}
	dup_command(token);
	while(command_n > 0)
	{
		minishell->pid->pid_n = fork();
		command_n--;
	}
	
}

// 	char *path;
// 	t_token *tmp;
// 	int i;

// 	tmp = token;
// 	path = get_the_command(pipex);
// 	if (!path)	
// 	{
// 		ft_putstr_fd("No such file or directory\n", 2);
// 		free_all(pipex);
// 		exit (EXIT_FAILURE);
// 	}
// 	if (cmd_index > 0)
// 		dup2(pipex->pipes[cmd_index - 1][0], STDIN_FILENO);
// 	if (cmd_index < pipex->num_cmds - 1)
// 		dup2(pipex->pipes[cmd_index][1], STDOUT_FILENO);
// 	i = 0;
// 	while (i < pipex->num_cmds - 1)
// 	{
// 		close(pipex->pipes[i][0]);
// 		close(pipex->pipes[i][1]);
// 		i++;
// 	}
// 	token = tmp;
// 	// while(token && ft_strcmp(token->value, "|") != 0)
// 	// {
// 	// 	ft_printf("%s\n", token->value);
// 	// 	command[i] = token->value;
// 	// 	ft_printf("commande  = %s\n", command[i]);
// 	// 	token = token->next;
// 	// 	i++;
// 	// }	
// 	ft_printf("%s\n", token->value);
// 	if (execve(path, minishell->command_exac, pipex->ev) == -1)
// 		error_execve(pipex);
// }
// // static void next_command(t_token *token)
// // {
// // 	token = token->next;
// // 	while((token->next) && (ft_strcmp(token->type, "commande") == 1)){
// // 		token = token->next;
// // 	}
// // 	token = token->next;
// // 	ft_printf("%s\n", token->value);
// // }

// void army_of_fork(char **ev, t_pipex *pipex, t_token *token, t_minishell *minishell)
// {
// 	int i;
// 	pid_t pid;

// 	find_the_path(ev, pipex);
// 	split_the_path(pipex);
// 	pipex->num_cmds = count_pipe(token);
// 	pipex->pipes = malloc(sizeof(int *) * (pipex->num_cmds - 1));

// 	i = 0;
// 	while (i < pipex->num_cmds - 1)
// 	{
// 		pipex->pipes[i] = malloc(sizeof(int) * 2);
// 		if (pipe(pipex->pipes[i]) == -1)
// 		{
// 			perror("Pipe creation failed");
// 			free_all(pipex);
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	// while(token && ft_strcmp(token->value, "|") != 0)
// 	// 	token = token->next;
// 	i = 0;
// 	while (i < pipex->num_cmds)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("Fork failed");
// 			free_all(pipex);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			execute_command(pipex, i, token, minishell);
// 		}
// 		if (i > 0)
// 			close(pipex->pipes[i - 1][0]);
// 		if (i < pipex->num_cmds - 1)
// 			close(pipex->pipes[i][1]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < pipex->num_cmds)
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < pipex->num_cmds - 1)
// 	{
// 		free(pipex->pipes[i]);
// 		i++;
// 	}
// 	free(pipex->pipes);