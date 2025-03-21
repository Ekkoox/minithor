/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2025/03/19 21:30:33 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_execve(t_pipex *pipex, t_minishell *minishell, t_token *token)
{
	ft_printf("bash: %s: Is a directory\n", token->value);
	repos_army(pipex, minishell->sup_command, token);
	mini_free(minishell, pipex, token, 1);
	free_env_list(minishell);
	free_tok_list(token, 0);
	exit(126);
}


static void check_command(t_token *token, t_token *tmp, int *c)
{
	while (token->next)
		{
			if (ft_strcmp(token->type, "pipe") == 0)
				break ;
			if (ft_strcmp(token->value, ">>") == 0)
				token = token->next;
			*c = *c + 1;
			token = token->next;
		}
	token = tmp;
}

static t_token *cherch_next_command(t_token *token, t_token *tmp, int *c, char *command, int *cmd_index)
{
		while (ft_strcmp(token->type, command) != 0
			&& token->index != *cmd_index + 1)
			token = token->next;
		while (token->next && ft_strcmp(token->type, "pipe") != 0)
		{
			if (ft_strcmp(token->value, ">>") == 0)
				token = token->next;
			*c = *c + 1;
			token = token->next;
		}
		token = tmp;
		while (ft_strcmp(token->type, command) != 0
			&& token->index != *cmd_index + 1)
				token = token->next;
		return (token);
}


static void	get_the_next_command(t_token *token, t_minishell *minishell,
		char *command, int *cmd_index)
{
	t_token	*tmp;
	int		y;
	int		c;

	tmp = token;
	y = 0;
	c = 0;
	if (*cmd_index == 0)
		check_command(token, tmp, &c);
	else
		token = cherch_next_command(token, tmp, &c, command, cmd_index);
	minishell->command_exac = ft_calloc(sizeof(char *), c + 1);
	while (y < c && token->next)
	{
		if (ft_strcmp(token->value, ">>") == 0)
			token = token->next;
		if ((ft_strcmp(token->type, "commande") == 0) || (ft_strcmp(token->type,
					"trash") == 0) || (ft_strcmp(token->type, "argument") == 0) )
			minishell->command_exac[y] = ft_strdup(token->value);
		token = token->next;
		y++;
	}
	minishell->command_exac[y] = NULL;
}

int	 find_the_thing(t_token *token, char *thing, int flag)
{
	t_token	*tmp;

	tmp = token;
	while (token->next)
	{
		if (ft_strcmp(token->value, thing) == 0 || ft_strcmp(token->type,
				thing) == 0)
		{
			token = tmp;
			return (0);
		}
		if (ft_strcmp(token->type, "pipe") == 0 && flag == 0)
		{
			token = tmp;
			return (1);
		}
		token = token->next;
	}
	token = tmp;
	return (1);
}

static void dup_redirect(t_token *token, t_pipex *pipex, t_token *tmp)
{
		tmp = token;
		while ((ft_strcmp(token->type, "redirect output") != 0)
			&& (ft_strcmp(token->type, "redirect input") != 0))
			token = token->next;
		if (ft_strcmp(token->value, ">") == 0)
			dup2(pipex->fd, STDOUT_FILENO);
		else if (ft_strcmp(token->value, ">>") == 0)
			dup2(pipex->fd, STDOUT_FILENO);
		else if (ft_strcmp(token->value, "<") == 0)
			dup2(pipex->fd, STDIN_FILENO);
		close(pipex->fd);
		token = tmp;
}

static void close_dup(t_pipex *pipex, int *cmd_index, t_token *tmp)
{
	int i;

	i = 0;
	if (*cmd_index == 0)
			dup2(pipex->pipes[0][1], STDOUT_FILENO);
		else if (*cmd_index < pipex->num_cmds - 1)
		{
			dup2(pipex->pipes[*cmd_index - 1][0], STDIN_FILENO);
			dup2(pipex->pipes[*cmd_index][1], STDOUT_FILENO);
		}
		else
			dup2(pipex->pipes[*cmd_index - 1][0], STDIN_FILENO);
		while (i < pipex->num_cmds - 1)
		{
			close(pipex->pipes[i][0]);
			close(pipex->pipes[i][1]);
			i++;
		}
		free_tab_int(pipex->pipes, count_command(tmp));
}

static void free_error_execut(t_minishell *minishell, t_pipex *pipex, t_token *token)
{
		mini_free(minishell, pipex, token, 1);
		free_tab_int(pipex->pipes, pipex->num_cmds);
		free_env_list(minishell);
		free_tok_list(token, 0);
		free_tab(minishell->sup_command);
		exit(127);
}

static void	execute_command(t_pipex *pipex, t_minishell *minishell,
		int *cmd_index, t_token *token, char *command)
{
	char	*path;
	t_token	*tmp;

	pipex->command_1 = command;
	tmp = token;
	check_error(token);
	path = get_the_command(pipex);
	if (path == NULL)
		free_error_execut(minishell, pipex, token);
	//check_permissions(path);
	free_tab(minishell->command_exac);
	get_the_next_command(token, minishell, command, cmd_index);
	if (find_the_thing(tmp, "file", 1) == 0 && find_the_thing(tmp, "pipe", 1) == 0)
		while (ft_strcmp(token->value, minishell->command_exac[0]) != 0)
				token = token->next;
	if (find_the_thing(token, "file", 1) == 0)
		dup_redirect(token, pipex, tmp);
	else if (count_pipe(tmp) > 0)
		close_dup(pipex, cmd_index, tmp);
	if (execve(path, minishell->command_exac, pipex->ev) == -1)
		error_execve(pipex, minishell, token);
}

static void	creat_pipeline(t_pipex *pipex, t_token *token)
{
	int		i;
	int		c;
	t_token	*tmp;

	i = 0;
	c = 0;
	tmp = token;
	while (token->next)
	{
		if (ft_strcmp(token->type, "pipe") == 0)
			c++;
		token = token->next;
	}
	pipex->pipes = ft_calloc(sizeof(int *), c);
	if (!pipex->pipes)
		return ;
	while ((c) > i)
	{
		pipex->pipes[i] = ft_calloc(sizeof(int), 2);
		if (!pipex->pipes[i])
			return ;
		pipe(pipex->pipes[i]);
		i++;
	}
	token = tmp;
}

static char	**creat_tab_command(t_token *token, int command_n)
{
	char	**res;
	t_token	*tmp;
	int		i;
	int		flag;

	res = ft_calloc(sizeof(char *), command_n + 2);
	if (!res)
		return (NULL);
	i = 0;
	flag = 0;
	tmp = token;
	while (token->next)
	{
		if ((ft_strcmp(token->type, "commande") == 0 || ft_strcmp(token->type, "trash") == 0) && (flag == 0))
		{
			res[i] = ft_strdup(token->value);
			if (!res[i])
				return (NULL);
			flag = 1;
			i++;
		}
		if (ft_strcmp(token->type, "pipe") == 0)
			flag = 0;
		token = token->next;
	}
	res[i] = NULL;
	token = tmp;
	return (res);
}

int	count_command(t_token *token)
{
	int		i;
	int		flag;
	t_token	*tmp;

	i = 0;
	flag = 0;
	tmp = token;
	while (token->next)
	{
		if ((ft_strcmp(token->type, "commande") == 0 || ft_strcmp(token->type,
					"trash") == 0) && (flag == 0))
		{
			i++;
			flag = 1;
		}
		if (ft_strcmp(token->type, "pipe") == 0)
			flag = 0;
		token = token->next;
	}
	token = tmp;
	return (i);
}

static void cherch_the_command(t_pipex *pipex, t_minishell *minishell, t_token *token, char **command, int i)
{
	int c;
	int status;
	pid_t pid;

	c = i - 1;
	status = 0;
	c++;
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		execute_command(pipex, minishell, &c, token, command[c]);
	if (i > 0)
		close(pipex->pipes[i - 1][0]);
	if (i < pipex->num_cmds - 1)
		close(pipex->pipes[i][1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_var = WEXITSTATUS(status);
}

void	army_of_fork(char **ev, t_pipex *pipex, t_minishell *minishell,
		t_token *token)
{
	int i;
	char **command;
	t_token *tmp;

	tmp = token;
	find_the_path(ev, pipex);
	split_the_path(pipex);
	pipex->num_cmds = count_command(token);
	if (pipex->num_cmds == 0)
		return ;
	creat_pipeline(pipex, token);
	command = creat_tab_command(token, pipex->num_cmds);
	minishell->sup_command = command;
	i = 0;
	while (i < pipex->num_cmds)
	{
		cherch_the_command(pipex, minishell, token, command, i);
		i++;
	}
	while (i < pipex->num_cmds)
	{
		wait(NULL);
		i++;
	}
	repos_army(pipex, command, tmp);
}
