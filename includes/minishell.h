/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:28:48 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/19 17:01:37 by razouani         ###   ########.fr       */
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

// SIGNAL

void 					handle_sigint(int sig);

// BUILTIN
int						ft_pwd(t_token *token);
int						ft_echo(t_token *token);
int						ft_cd(t_token *token, t_env *env);
int						ft_export(t_env *env, t_token *token);
int						ft_env(t_minishell *minishell);
int						is_builtin(t_minishell *minishell, t_token *token);

// HEREDOC
void 					close_fd(int sig);
int						count_heredoc(t_token *token);
int 					execut_heredoc(t_token *token);
int						heredoc(t_token *token, t_token **head,
							int *nb_heredoc);

// UTILS
void					handle_sigint(int sig);
char					**ft_split_env(char const *s, char c);

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
int						count_quote(char *mot);
int						is_space(char *str, int *index);
int						search_command_for_token(t_pipex *pipex, char *mot);
int						tokenisation(t_token *token, t_minishell *minishell,
							t_pipex *pipex);
char					*in_quote(char *mot, int quote);
void					check_token(t_token *token, t_env *env);
void					clear_quote(char *buffer, char *dest, int *index, int start,
							int *index_dest);

//FREE
void 					repos_army(t_pipex *pipex, char **command);
void 					free_tok(t_token *token, t_minishell *minishell, t_pipex *pipex);
void 					free_env_list(t_env *env);
void    				free_tok_list(t_token *token);
void    				free_minishell_list(t_minishell *minishell);
void 					free_tab(char **tab);
void					mini_free(t_minishell *minishell, t_pipex *pipex);

#endif