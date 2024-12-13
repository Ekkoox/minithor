/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:28:48 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/13 16:51:21 by enschnei         ###   ########.fr       */
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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

enum					e_token
{
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECTION,
};

typedef struct s_pid
{
	pid_t				pid_n;
	struct s_pid		*next;
}						t_pid;

typedef struct s_env
{
	char				*type;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				flag;
	char				*type;
	char				*value;
	char				*heredoc;
	struct s_token		*next;
	struct s_token		*prev;
	
}						t_token;

typedef struct s_minishell
{
	int					flag_builtin;
	int					flag;
	char				*current;
	char				*buffer;
	char				**command_exac;
	t_token				*token;
	t_env				*env;
	t_pid				*pid;
}						t_minishell;

typedef struct s_historique
{
	char				*commande;
	struct s_historique	*next;
	struct s_historique	*prev;
}						t_historique;

typedef struct s_pipex
{
	int					*fd;
	int					**pipes;
	int					num_cmds;
	char				**ev;
	char				**path;
	char				*file_1;
	char				*command_1;
	char				*ligne_path;
	t_minishell			*minishell;
	pid_t				pid;
}						t_pipex;

// BUILTIN
int 					is_builtin(t_minishell *minishell, t_token *token);

// HEREDOC
int						heredoc	(t_token *token, t_token **head);

// UTILS
void 					handle_sigint(int sig);
char					**ft_split_env(char const *s, char c);

// FONCTION
int						ft_cd(t_token *token, t_env *env);
int						ft_pwd(t_token *token);
int						ft_env(t_minishell *minishell);
int						ft_echo(t_token *token);

// PROMPT
int						exit_prompt(char *buffer);
int						error_prompt(char *buffer, ssize_t bytes_read);
int						creat_the_prompt(char **ev, t_pipex *pipex,
							t_token *token, t_minishell *minishell);

// PIPE
void					free_all(t_pipex *pipex);
void					army_of_fork(char **ev, t_pipex *pipex,
							t_minishell *minishell, t_token *token);
char					*get_the_command(t_pipex *pipex);
char					**split_the_path(t_pipex *pipex);
char					*find_the_path(char **ev, t_pipex *pipex);
char					*search_the_path(t_pipex *pipex, char *command);

// TOKEN
void					check_token(t_token *token, t_env *env);
int						tokenisation(t_token *token, t_minishell *minishell,
							t_pipex *pipex);
int						search_command_for_token(t_pipex *pipex, char *mot);

#endif