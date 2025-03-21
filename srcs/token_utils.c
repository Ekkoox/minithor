/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:03:28 by enschnei          #+#    #+#             */
/*   Updated: 2025/03/19 22:12:21 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_the_path_for_token(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->ligne_path = NULL;
	while (pipex->ev[i])
	{
		if (ft_strncmp(pipex->ev[i], "PATH=", 5) == 0)
		{
			pipex->ligne_path = pipex->ev[i];
			break ;
		}
		i++;
	}
	return (pipex->ligne_path);
}

static char	**split_the_path_for_the_token(t_pipex *pipex)
{
	if (!pipex->ligne_path)
		return (NULL);
	pipex->path = ft_split(pipex->ligne_path + 5, ':');
	if (!pipex->path)
		return (NULL);
	return (pipex->path);
}

static char	*search_the_path_for_the_token(t_pipex *pipex, char *command)
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

static int get_the_command_for_the_token(t_pipex *pipex)
{
	char	*path;
	
	if (!pipex->command_1)
		ft_putstr_fd("Malloc error\n", 2);
	if (!ft_strchr(pipex->command_1, '/') && pipex->command_1[0] != '.')
	{
		path = search_the_path_for_the_token(pipex, pipex->command_1);
		if (!path)
			return (EXIT_FAILURE);
		return (free(path), EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	search_command_for_token(t_pipex *pipex, char *mot)
{
	pipex->command_1 = mot;
	find_the_path_for_token(pipex);
	split_the_path_for_the_token(pipex);
	if (get_the_command_for_the_token(pipex) == 0)
	{
		free_tab(pipex->path);
		pipex->path = NULL;
		return (0);
	}
	if (pipex->flag == 1)
	{
		free_tab(pipex->path);
		pipex->path = NULL;
	}
	return (1);
}
