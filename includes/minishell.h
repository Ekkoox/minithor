/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:28:48 by enschnei          #+#    #+#             */
/*   Updated: 2024/10/17 16:48:32 by enschnei         ###   ########.fr       */
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

typedef struct s_pipex
{
	int				fd[2];
	char			*file_1;
	char			*command_1;
	char			*ligne_path;
	char			**ev;
	char			**path;
	pid_t			pid;
}					t_pipex;

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
	t_pipex			pipex;
	t_token			token;
}					t_minishell;

// PROMPT
int					creat_the_prompt(int ac, char **av, char **ev,
						t_pipex *pipex, t_token *token, t_minishell *minishell);

// PIPE
void				free_all(t_pipex *pipex);
void				army_of_fork(char **ev, t_pipex *pipex, t_token *token);
char				*get_the_command(t_pipex *pipex);
char				**split_the_path(t_pipex *pipex);
char				*find_the_path(char **ev, t_pipex *pipex);
char				*search_the_path(t_pipex *pipex, char *command);

// TOKEN
int					tokenisation(t_token *token, t_minishell *minishell, t_pipex *pipex);
int					search_command_for_token(t_pipex *pipex, char *mot);

# endif