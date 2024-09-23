/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:53:42 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/23 21:01:24 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_pipex *pipex)
{
	if (pipex->path)
		ft_free(pipex->path, ft_count_line_split(pipex->path));
	// ft_free(pipex->command_1, ft_count_line_split(pipex->command_1));
	exit(EXIT_SUCCESS);
}

char	*find_the_path(int ac, char **av, char **ev, t_pipex *pipex)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	pipex->ligne_path = NULL;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], "PATH=", 5) == 0)
		{
			pipex->ligne_path = ev[i];
			break ;
		}
		i++;
	}
	return (pipex->ligne_path);
}

char	**split_the_path(t_pipex *pipex)
{
	if (!pipex->ligne_path)
		return (NULL);
	pipex->path = ft_split(pipex->ligne_path + 5, ':');
	if (!pipex->path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		// ft_free(pipex->command_1, ft_count_line_split(pipex->command_1));
		exit(EXIT_FAILURE);
	}
	return (pipex->path);
}

static char	*search_the_path(t_pipex *pipex, char *command)
{
	int		i;
	char	*tmp;
	char	*path;

	if (pipex->path == NULL)
		return (NULL);
	i = 0;
	tmp = ft_strjoin("/", command);
	if (!tmp)
		return (NULL);
	while (pipex->path[i])
	{
		path = ft_strjoin(pipex->path[i], tmp);
		if (!path)
			return (free(tmp), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free(tmp), path);
		free(path);
		i++;
	}
	free(tmp);
	return (NULL);
}

char	*get_the_command(t_pipex *pipex)
{
	char	*path;
	
	if (!pipex->command_1)
	{
		ft_putstr_fd("Malloc error\n", 2);
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	if (!ft_strchr(pipex->command_1, '/') && pipex->command_1[0] != '.')
	{
		path = search_the_path(pipex, pipex->command_1);
		if (!path)
		{
			ft_putstr_fd("Command not found\n", 2);
			free_all(pipex);
			exit(EXIT_FAILURE);
		}
		return (path);
	}
	if (access(pipex->command_1, F_OK | X_OK) == 0)
		return (pipex->command_1);
	return (NULL);
}