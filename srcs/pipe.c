/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/19 16:08:29 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void error_execve(t_pipex *pipex)
{
	ft_putstr_fd("Execve error\n", 2);
	free_all(pipex);
	exit(EXIT_FAILURE);
}

static void get_the_next_command(t_token *token, t_minishell *minishell, char *command)
{
	t_token *tmp;
	int i;
	int c = 0;

	tmp = token;
	i = 0;
	while(ft_strcmp(token->value, command) != 0 && token->next)
		token = token->next;
	while(token->next)
	{
		if (ft_strcmp(token->type, "pipe") == 0)
			break;
		i++;
		token = token->next;
	}
	free(minishell->command_exac);
	minishell->command_exac = ft_calloc(sizeof(char *), i + 1);
	token = tmp;
	while(c < i)
	{
		if (ft_strcmp("<<", token->value) == 0)
		{
			c++;
			token = token->next;
		}
		else
			minishell->command_exac[c] = ft_strdup(token->value);
		c++;
		token = token->next;
	}
	minishell->command_exac[c] = NULL;
}

static void execute_command(t_pipex *pipex, t_minishell *minishell, int cmd_index,t_token *token, char *command)
{
	char *path;
	int i;
	(void)token;
	
	pipex->command_1 = command;
	path = get_the_command(pipex);
	int c = 0;
	while(minishell->command_exac[c])
	{
		free(minishell->command_exac[c]);
		c++;
	}
	get_the_next_command(token, minishell, command);
	if (!path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	if (token->flag == 1)
	{
		int fd = open("Tmp_files", O_RDONLY);
		dup2(fd, STDIN_FILENO);	
	}
	else if (cmd_index > 0)
		dup2(pipex->pipes[cmd_index - 1][0], STDIN_FILENO);
	else if (cmd_index < pipex->num_cmds - 1)
		dup2(pipex->pipes[cmd_index][1], STDOUT_FILENO);
	i = 0;
	while (i < pipex->num_cmds - 1){
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	ft_printf("%s\n", minishell->command_exac[0]);
	ft_printf("%s\n", minishell->command_exac[1]);
	if (execve(path, minishell->command_exac, pipex->ev) == -1)
		error_execve(pipex);
}

static void creat_pipelin(t_pipex *pipex, t_token *token)
{
	int i;
	int c;
	t_token *tmp;

	i = 0;
	c = 0;
	tmp = token;
	while(token->next)
	{
		if (ft_strcmp(token->type, "commande") == 0)
			c++;
		token = token->next;
	}
	pipex->pipes = ft_calloc(sizeof(int *), c - 1);
	while((c - 1) > i)
	{
		pipex->pipes[i] = ft_calloc(sizeof(int), 2);
		pipe(pipex->pipes[i]); 
		i++;
	}
	token = tmp;
}

static char **creat_tab_command(t_token *token, int command_n)
{
	char **res;
	t_token *tmp;
	int i;

	res = ft_calloc(sizeof(char *), command_n + 1);
	i = 0;
	tmp = token;
	while(i < command_n)
	{
		if (i == 0){
			res[i] = ft_strdup(token->value);
		}
		else if ((ft_strcmp(token->type, "pipe") == 0) && i != 0){
			res[i] = ft_strdup(token->next->value);
			token = token->next;
		}
		i++;
		token = token->next;
	}
	res[i] = NULL;
	token = tmp;
	return(res);
}

static int count_command(t_token *token)
{
	int i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while(token->next)
	{
		if (i == 0)
			i++;
		if (ft_strcmp(token->type, "pipe") == 0)
			if (token->next)
				i++;
		token = token->next;
	}
	token = tmp;
	return(i);
}




void army_of_fork(char **ev, t_pipex *pipex, t_minishell *minishell, t_token *token)
{
	int i;
	pid_t pid;

	find_the_path(ev, pipex);
	split_the_path(pipex);
	pipex->num_cmds = count_command(token);
	creat_pipelin(pipex, token);
	char **command = creat_tab_command(token, pipex->num_cmds);

	int c = -1;
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
		c++;
		if (pid == -1)
		{
			perror("Fork failed");
			free_all(pipex);
			exit(EXIT_FAILURE);
		}
		if (pid == 0){
			//ft_printf("%s|||\n", command[c]);
			execute_command(pipex, minishell, i, token, command[c]);
		}
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
	// i = 0;
	// while (i < pipex->num_cmds - 1)
	// {
	// 	free(pipex->pipes[i]);
	// 	i++;
	// }
	repos_army(pipex, command);
}
