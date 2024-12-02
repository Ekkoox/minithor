/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:21:20 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/02 16:09:27 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char *dup_spe(char *str)
// {
// 	int i;
// 	char *res;

// 	i = 0;
// 	res = ft_calloc(sizeof(char), ft_strlen(str) + 1);
// 	while(str[i])
// 	{
// 		while()
// 		i++;
// 	}
// }


static void error_execve(t_pipex *pipex)
{
	ft_putstr_fd("Execve error\n", 2);
	free_all(pipex);
	// exit(EXIT_FAILURE);
}

static void get_the_next_command(t_token *token, t_minishell *minishell, char *command)
{
	t_token *tmp;
	int i;
	int c = 0;

	tmp = token;
	i = 0;
	while(!(ft_strcmp(token->value, command) == 0) && token->next)
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
	while(c < i){
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
	while(minishell->command_exac[c]){
		free(minishell->command_exac[c]);
		c++;
	}
	get_the_next_command(token, minishell, command);
	if (!path){
		ft_putstr_fd("No such file or directory\n", 2);
		free_all(pipex);
		// exit(EXIT_FAILURE);
	}
	if (cmd_index > 0)
		dup2(pipex->pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < pipex->num_cmds - 1)
		dup2(pipex->pipes[cmd_index][1], STDOUT_FILENO);
	i = 0;
	while (i < pipex->num_cmds - 1){
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
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

void	army_of_fork(char **ev, t_pipex *pipex, t_minishell *minishell)
{
	int	id_fork;

	find_the_path(ev, pipex);
	split_the_path(pipex);
	pipex->num_cmds = count_command(token);
	creat_pipelin(pipex, token);
	char **command = creat_tab_command(token, pipex->num_cmds);
	// ft_printf("%s\n", command[0]);
	// ft_printf("%s\n", command[1]);
	// ft_printf("%s\n", command[2]);
	// ft_printf("%s\n", command[3]);
	pipex->pipes = malloc(sizeof(int *) * (pipex->num_cmds - 1));
	int c = -1;

	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		ft_printf("Error with the fork\n");
		free_all(pipex);
		// exit(EXIT_FAILURE);
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
	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}

//!!!regarde pour les cas comme celui la " ls | " dans le bash ca ouvre comme un heardoc dans le miens ca casse tout
//regarde aussi pour ce cas la "ls|pwd" tout coller c'est senser fonctionner pas ici
//regarde aussi celui la "ls " une commande suivi d'un espace ne fonctionne pas je pense a cause des strdup qui duplique avec les espace

//solution
//1: tu peux fermer tout le programme si il y a rien juste apres a pipe mais un peu barbar sinon pas d'idee pour lui
//2: dans la token on peut faire en sorte de compte comme des espace les pipe. "a dester"
//3: faire un strdup modifier qui suprime les espace dans toute la string a copier mais l'implementer au copie de commande uniquement ou alors un stdup qui suprime espace avamt et apres uniquement.
