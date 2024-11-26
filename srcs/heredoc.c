/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:49:43 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/26 17:12:58 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int creat_the_heredoc(t_token *token)
{
    char *buffer;
    int fd;
    ssize_t bytes_read;
    
    bytes_read = 0;
    fd = open("Tmp_file", O_RDWR | O_TRUNC | O_CREAT, 0644);
    if (!fd)
        return (EXIT_FAILURE);
    while(1)    
    {
        buffer = readline("heredoc>");
        if (!buffer)
        {
            dprintf(2, "bash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", __LINE__, token->next->value);
            return (EXIT_FAILURE);
        }
        if (ft_strcmp(token->next->value, buffer) == 0)
        {
            unlink("Tmp_file");
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

int heredoc(t_token *token)
{
    int pid;
    
    if (!token->next->value)
        return(EXIT_FAILURE);
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == -1)
        return(ft_putstr_fd("Error fork heredoc", 2), EXIT_FAILURE);
    if (pid == 0)
    {
        signal(SIGINT, close_fd);
        creat_the_heredoc(token);
        exit (EXIT_SUCCESS);
    }
    wait(NULL);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_sigint);
    return (EXIT_SUCCESS);
}
