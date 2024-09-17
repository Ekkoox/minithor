/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:28:48 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/17 20:07:02 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd[2];
	char	*ligne_path;
	char	*file_1;
	char	**ev;
	char	**command_1;
	char	**path;
	pid_t	pid;
}			t_pipex;

typedef struct s_minishell
{
	t_pipex	pipex;
}			t_minishell;

// PROMPT
int		creat_the_prompt(int ac, char **av, char **ev, t_pipex *pipex);

// PIPE
void		free_all(t_pipex *pipex);
void		army_of_fork(int ac, char **av, char **ev, t_pipex *pipex);
char		*get_the_command(t_pipex *pipex);
char		**split_the_path(t_pipex *pipex);
char		*find_the_path(int ac, char **av, char **ev, t_pipex *pipex);

#endif