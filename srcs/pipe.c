/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/28 19:39:09 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void error_execve(t_pipex *pipex, t_minishell *minishell, t_token *token)
{
	ft_printf("bash: %s: Is a directory\n", token->value);
	repos_army(pipex, minishell->sup_command);
	mini_free(minishell, pipex, token, 1);
	free_env_list(minishell->env);
	free_tok_list(token, 0);
	//free_tab(minishell->sup_command);
	exit(126);
}

static void get_the_next_command(t_token *token, t_minishell *minishell, char *command, int *cmd_index)
{
	(void)*command;
	t_token *tmp;
	//int i;
	int y;
	int c;

	tmp = token;
	//i = 0;
	y = 0;
	c = 0;
	if (*cmd_index == 0)
	{
		while(token->next)
		{
			if (ft_strcmp(token->type, "pipe") == 0)
				break;
			if (ft_strcmp(token->value, ">>") == 0)
				token = token->next;
			c++;
			token = token->next;
		}
		token = tmp;
	}
	else
		{
			while(ft_strcmp(token->type, command) != 0 && 
			token->index != *cmd_index + 1)
				token = token->next;
			while(token->next && ft_strcmp(token->type, "pipe") != 0)
			{
				if (ft_strcmp(token->value, ">>") == 0)
					token = token->next;
				c++;
				token = token->next;
			}
			token = tmp;
			while(ft_strcmp(token->type, command) != 0 && 
			token->index != *cmd_index + 1)
				token = token->next;
		}
	minishell->command_exac = ft_calloc(sizeof(char *), c + 1);
	// ft_printf("asdasd%s\n", token->value);
	// ft_printf("%d\n", c);
	while(y < c && token->next)
	{
		if (ft_strcmp(token->value, ">>") == 0)
			token = token->next;
		if ((ft_strcmp(token->type, "commande") == 0) || (ft_strcmp(token->type, "trash") == 0) || (ft_strcmp(token->type, "argument") == 0))
			minishell->command_exac[y] = ft_strdup(token->value);
		// ft_printf("%s\n", minishell->command_exac[y]);
		token = token->next;
		y++;
	}
	minishell->command_exac[y] = NULL;
}

static int	 find_the_thing(t_token *token, char *thing)
{
	t_token *tmp;

	tmp = token;
	while(token->next)
	{
		if (ft_strcmp(token->value, thing) == 0 || ft_strcmp(token->type, thing) == 0)
		{
			token = tmp;
			return (0);
		}
		if (ft_strcmp(token->type, "pipe") == 0 )
		{
			token = tmp;
			return (1);
		}
		token = token->next;
	}
	token = tmp;
	return (1);
}


static void execute_command(t_pipex *pipex, t_minishell *minishell, int *cmd_index,t_token *token, char *command)
{
	char *path;
	t_token *tmp;
	int i;
	
	pipex->command_1 = command;
	tmp = token;
	path = get_the_command(pipex);
	if (path == NULL)
	{
		mini_free(minishell, pipex, token, 1);
		free_env_list(minishell->env);
		free_tok_list(token, 0);
		free_tab(minishell->sup_command);
		exit(127);
	}
	free_tab(minishell->command_exac);	
	get_the_next_command(token, minishell, command, cmd_index);
	if (!path)
	{
		ft_putstr_fd("1 No such file or directory\n", 2);
		mini_free(minishell, pipex, token, 1);
		free_env_list(minishell->env);
		free_tok_list(token, 0);
		free_tab(minishell->sup_command);
		exit(127);
	}
	// ft_printf("%s\n", minishell->command_exac[0]);
	// ft_printf("%s\n", minishell->command_exac[1]);
	while(ft_strcmp(token->value, minishell->command_exac[0]) != 0)
		token = token->next;
	if (find_the_thing(token, "file") == 0)
	{
		tmp = token;
		while ((ft_strcmp(token->type, "redirect output") != 0) &&
		 (ft_strcmp(token->type, "redirect input") != 0))
				token = token->next;
		if (ft_strcmp(token->value, ">") == 0)
		{
			dup2(pipex->fd, STDOUT_FILENO);
		}
		else if (ft_strcmp(token->value, ">>") == 0)
			dup2(pipex->fd, STDOUT_FILENO);
		else if (ft_strcmp(token->value, "<") == 0)
			dup2(pipex->fd, STDIN_FILENO);
		close(pipex->fd);
		token = tmp;
	}
	if (count_pipe(tmp) > 0)
	{
		// ft_printf("asdasda%s\n", token->value);
		if (*cmd_index == 0)
			dup2(pipex->pipes[0][1], STDOUT_FILENO);
		else if (*cmd_index < pipex->num_cmds - 1)
		{
			dup2(pipex->pipes[*cmd_index - 1][0], STDIN_FILENO);
       		dup2(pipex->pipes[*cmd_index][1], STDOUT_FILENO);
		}
		else
			dup2(pipex->pipes[*cmd_index - 1][0], STDIN_FILENO);
		i = 0;
		while (i < pipex->num_cmds - 1)
		{
			close(pipex->pipes[i][0]);
			close(pipex->pipes[i][1]);
			i++;
		}
	}
	// ft_printf("%s\n", minishell->command_exac[0]);
	// ft_printf("%s\n", minishell->command_exac[1]);	
	
	//if (is_command_builtin(minishell->command_exac[0], token, minishell) == 0)
		if (execve(path, minishell->command_exac, pipex->ev) == -1)
			error_execve(pipex, minishell, token);
}

static void creat_pipeline(t_pipex *pipex, t_token *token)
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
	if (!pipex->pipes)
		return ;
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
	int flag;

	res = ft_calloc(sizeof(char *), command_n + 1);
	if (!res)
		return(NULL);
	i = 0;
	flag = 0;
	tmp = token;
	while(token->next)
	{
		// if (i == 0 && ft_strcmp(token->type, "commande") == 0)
		// 	res[i] = ft_strdup(token->value);
		// else if ((ft_strcmp(token->type,command: "pipe") == 0) && i != 0){
		// 	res[i] = ft_strdup(token->next->value);
		// 	if (!res[i])
		// 		return(NULL);
		// 	token = token->next;
		// }
		if ((ft_strcmp(token->type, "commande") == 0 || ft_strcmp(token->type, "trash") == 0) && (flag == 0))
		{
			res[i] = ft_strdup(token->value);
			if (!res[i])
				return(NULL);
			flag = 1;
			i++;
		}
		if (ft_strcmp(token->type, "pipe") == 0)
			flag = 0;
		token = token->next;
	}
	res[i] = NULL;
	token = tmp;
	return(res);
}

int count_command(t_token *token)
{
	int i;
	int flag;
	t_token *tmp;

	i = 0;
	flag = 0;
	tmp = token;
	while(token->next)
	{
		if ((ft_strcmp(token->type, "commande") == 0 || ft_strcmp(token->type, "trash") == 0) && (flag == 0))
		{
			i++;
			flag = 1;
		}
		if (ft_strcmp(token->type, "pipe") == 0)
			flag = 0;
		token = token->next;
	}
	token = tmp;
	return(i);
}

void army_of_fork(char **ev, t_pipex *pipex, t_minishell *minishell, t_token *token)
{
	int i;
	int status;
	pid_t pid;

	find_the_path(ev, pipex);
	split_the_path(pipex);
	pipex->num_cmds = count_command(token);
	if(pipex->num_cmds == 0)
	{
		ft_putstr_fd("2 No such file or directory\n", 2);
		return ;
	}
	creat_pipeline(pipex, token);
	char **command = creat_tab_command(token, pipex->num_cmds);
	minishell->sup_command = command;
	status = 0;
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
		c++;
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			free_all(pipex);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			// ft_printf("command: %s\n", command[0]);
			// ft_printf("command: %s\n", command[1]);
			// ft_printf(" %d\n", c);
			
			execute_command(pipex, minishell, &c, token, command[c]);
		}
		// if (pipex->fd)
		// 	close(pipex->fd);
		if (i > 0)
			close(pipex->pipes[i - 1][0]);
		if (i < pipex->num_cmds - 1)
			close(pipex->pipes[i][1]);
		waitpid(pid, &status, 0); 
		if (WIFEXITED(status))
			var_g = WEXITSTATUS(status);
		i++;
	}
	i = 0;
	while (i < pipex->num_cmds)
	{
		wait(NULL);
		i++;
	}
	repos_army(pipex, command);
}

// probleme commande
// /
// chmod 