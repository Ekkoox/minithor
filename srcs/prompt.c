/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2024/10/18 17:40:39 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_prompt(char *buffer, ssize_t bytes_read)
{
	if (!buffer)
	{
		perror("Error calloc");
		exit(EXIT_FAILURE);
	}
	if (bytes_read < 0)
	{
		perror("Error reading input");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	exit_prompt(char *buffer)
{
	if (ft_strcmp(buffer, "exit") == 0)
	{
		ft_putstr_fd("Bisous mon chou <3\n", 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*

while (str[i])
{
	if (is_redirect(str[i])
		redirect_management(str, &i)
}
*/

int	creat_the_prompt(int ac, char **av, char **ev, t_pipex *pipex, t_token *token, t_minishell *minishell)
{
	char	*buffer;
	size_t	buf_size;
	ssize_t	bytes_read;
	(void) av;

	buf_size = BUFFER_SIZE;
	bytes_read = 0;	
	buffer = (char *)ft_calloc(sizeof(char), buf_size);
	if (!buffer)
		error_prompt(buffer, bytes_read);
	while(1)
	{
		ft_putstr_fd(">", 1);
		buffer = readline(STDIN_FILENO);
		bytes_read = ft_strlen(buffer);
		buffer[bytes_read] = '\0';
		if (buffer[bytes_read - 1] == '\n')
			buffer[bytes_read - 1] = '\0';
		if (exit_prompt(buffer) == 0)
			break ;
		minishell->buffer = buffer;
		tokenisation(token, minishell, pipex);
		pipex->command_1 = token->value;
		army_of_fork(ac, buffer, ev, pipex, minishell);
	}
	if (bytes_read < 0)
		error_prompt(buffer, bytes_read);
	free(buffer);
	return (EXIT_SUCCESS);
}
