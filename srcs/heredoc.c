/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:49:43 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/10 23:47:17 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void delete(t_token *target)
// {
//     free(target->flag);
//     free(target->type);
//     free(target->value);
//     free(target->heredoc);
// }

  static void delete_node_heredoc(t_token *target, t_token **head)
{
    t_token *prev;
    t_token *tmp;
    int flag;

    prev = *head;
    tmp = *head;
    flag = 0;
    if (ft_strcmp((*head)->type, "heredoc") == 0)
    {
        *head = target->next;
        free(target);
        target = NULL;
    }
    else
        while((*head)->next)
        {
            (*head) = (*head)->next;
            if (ft_strcmp((*head)->type, "heredoc") == 0)
            {
                if (target->next->value != NULL){
                    flag = 1;
                    (*head) = target->next;
                }
                break;
            }
            prev = prev->next;
        }
    if (flag ==1){
        prev->next = (*head);
    }
    else
        (*head) = prev;
    ft_printf("%s\n", (*head)->value);
    free((*head)->next->value);
    free((*head)->next->type);
    free((*head)->next->heredoc);
    (*head)->next->type = NULL;
    (*head)->next->value = NULL;
    (*head)->next->heredoc =NULL;
    free((*head)->next);
    (*head)->next = ft_calloc(sizeof(t_token), 1);
    *head = tmp;
    
}

static void find_the_heredoc(t_token *token)
{
    int i = 0;
    int y = 0;

    while(token->value[i] != '<')
        i++;
    while (token->value[i] == '<' || token->value[i] == ' ')
        i++;
    token->heredoc = ft_calloc(sizeof(char), ft_strlen(token->value));
    if (!token->heredoc)
        return ;
    while (token->value[i])
        token->heredoc[y++] = token->value[i++];
    token->heredoc[y] = '\0';
}

static int creat_the_heredoc(t_token *token)
{
    char *buffer;
    int fd;

    fd = open("Tmp_file", O_RDWR | O_TRUNC | O_CREAT, 0644);
    if (!fd)
        return (EXIT_FAILURE);
    find_the_heredoc(token);
    while(1)    
    {
        buffer = readline("heredoc>");
        if (!buffer)
        {
            dprintf(2, "bash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", __LINE__, token->value);
            return (EXIT_FAILURE);
        }
        if (ft_strcmp(buffer, token->heredoc) == 0)
        {
            unlink("Tmp_file");
            free(token->heredoc);
            free(buffer);
            break ;
        }
        ft_putstr_fd(buffer, fd);
        write(fd, "\n", 1);
        free(buffer);
    }
    return (EXIT_FAILURE);
}

static void close_fd(int sig)
{
    (void) sig;
    close(0);
    ft_printf("\n");
    exit (EXIT_FAILURE);
}

int heredoc(t_token *token, t_token **head)
{
    int pid;
    int status;

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
    unlink("Tmp_file");
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_sigint);
    if (token->next != NULL)
        delete_node_heredoc(token, head);
    return (EXIT_SUCCESS);
}
