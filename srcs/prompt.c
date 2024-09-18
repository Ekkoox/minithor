/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/18 17:09:07 by enschnei         ###   ########.fr       */
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

int	creat_the_prompt(int ac, char **av, char **ev, t_pipex *pipex)
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
	ft_putstr_fd(">", 1);
	while ((bytes_read = read(STDIN_FILENO, buffer, buf_size - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (buffer[bytes_read - 1] == '\n')
			buffer[bytes_read - 1] = '\0';
		if (exit_prompt(buffer) == 0)
			break ;
		ft_putstr_fd(">", 1);
		pipex->command_1 = buffer;
		army_of_fork(ac, buffer, ev, pipex); //c de la merde
	}
	if (bytes_read < 0)
		error_prompt(buffer, bytes_read);
	free(buffer);
	return (EXIT_SUCCESS);
}
