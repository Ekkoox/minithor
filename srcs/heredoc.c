/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:49:43 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/18 15:03:23 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_token *target, t_token **head, t_token *prev,
		t_token *tmp, int flag)
{
	if (flag == 1)
	{
		prev->next = (*head);
		free(target->value);
		free(target->type);
		free(target->heredoc);
		target->type = NULL;
		target->value = NULL;
		target->heredoc = NULL;
		free(target);
		*head = tmp;
	}
	else
	{
		(*head) = prev;
		free(target->value);
		free(target->type);
		free(target->heredoc);
		target->type = NULL;
		target->value = NULL;
		target->heredoc = NULL;
		free(target);
		(*head)->next = ft_calloc(sizeof(t_token), 1);
		*head = tmp;
	}
}

static void	delete_node_heredoc(t_token **target, t_token **head)
{
	t_token	*prev;
	t_token	*tmp;
	int		flag;

	prev = *head;
	tmp = *head;
	flag = 0;
	if (ft_strcmp((*head)->type, "heredoc") == 0)
	{
		*head = (*target)->next;
		free((*target));
		(*target) = (*head);
		return ;
	}
	else
		while ((*head)->next)
		{
			(*head) = (*head)->next;
			if (ft_strcmp((*head)->type, "heredoc") == 0)
			{
				if ((*target)->next->value != NULL)
				{
					flag = 1;
					(*head) = (*target)->next;
				}
				break ;
			}
			prev = prev->next;
		}
	free_node((*target), head, prev, tmp, flag);
}

static void	find_the_heredoc(t_token *token)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (token->value[i] && token->value[i] != '<')
		i++;
	while (token->value[i] == '<' || token->value[i] == ' ')
		i++;
	token->heredoc = ft_calloc(sizeof(char), ft_strlen(token->value) - i + 1);
	if (!token->heredoc)
		return ;
	while (token->value[i])
		token->heredoc[y++] = token->value[i++];
	token->heredoc[y] = '\0';
}

static int	creat_the_heredoc(t_token *token)
{
	char	*buffer;
	int		fd;

	fd = open("Tmp_file", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (EXIT_FAILURE);
	find_the_heredoc(token);
	if (!token->heredoc)
		return (EXIT_FAILURE);
	while (1)
	{
		buffer = readline("heredoc>");
		if (!buffer)
		{
			dprintf(2, "bash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", __LINE__, token->heredoc);
			close(fd);
			free(token->heredoc);
			unlink("Tmp_file");
			return (EXIT_FAILURE);
		}
		if (ft_strcmp(buffer, token->heredoc) == 0)
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, fd);
		write(fd, "\n", 1);
		free(buffer);
	}
	free(token->heredoc);
	close(fd);
	unlink("Tmp_file");
	return (EXIT_SUCCESS);
}

int	heredoc(t_token *token, t_token **head, int *nb_heredoc)
{
	int	pid;
	int	status;

	token->flag = 1;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("Error fork heredoc");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, close_fd);
		if (creat_the_heredoc(token) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	if (execut_heredoc(*head))
		delete_node_heredoc(&token, head);
	else
		return ((*nb_heredoc = (*nb_heredoc) - 1), EXIT_FAILURE);
	(*nb_heredoc) = (*nb_heredoc) - 1;
	return (EXIT_SUCCESS);
}
