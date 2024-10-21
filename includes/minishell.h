/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:28:48 by enschnei          #+#    #+#             */
/*   Updated: 2024/10/18 17:41:24 by razouani         ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>


typedef struct s_token
{
	char			*type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
	int				flag;
	char			*current;
	char			*buffer;
	char			**command_exac;
	// t_pipex			*pipex;
	t_token			*token;
}					t_minishell;

typedef struct s_pipex
{
	int				fd[2];
	char			*file_1;
	char			*command_1;
	char			*ligne_path;
	char			**ev;
	char			**path;
	t_minishell		*minishell;
	pid_t			pid;
}					t_pipex;

// PROMPT
int					creat_the_prompt(int ac, char **av, char **ev,
						t_pipex *pipex, t_token *token, t_minishell *minishell);

// PIPE
void				free_all(t_pipex *pipex);
void				army_of_fork(int ac, char *av, char **ev, t_pipex *pipex, t_minishell *minishell);
char				*get_the_command(t_pipex *pipex);
char				**split_the_path(t_pipex *pipex);
char				*find_the_path(int ac, char **av, char **ev,
						t_pipex *pipex);
char				*search_the_path(t_pipex *pipex, char *command);

// TOKEN
int					tokenisation(t_token *token, t_minishell *minishell,
						t_pipex *pipex);
int					search_command_for_token(t_pipex *pipex, char *mot);

#endif