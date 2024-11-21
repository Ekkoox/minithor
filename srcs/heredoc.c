/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:49:43 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/21 18:39:47 by enschnei         ###   ########.fr       */
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
            return (EXIT_FAILURE);
        if (ft_strcmp(token->next->value, buffer) == 0)
        {
            unlink("Tmp_file");
            break ;
        }
        ft_putstr_fd(buffer, fd);
        write(fd, "\n", 1);
        free(buffer);
    }
    return (EXIT_FAILURE);
}

static void close_fd(int tmp)
{
    (void) tmp;
    close(0);
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
    if (!pid)
    {
        signal(SIGINT, close_fd);
        creat_the_heredoc(token);
        exit (EXIT_SUCCESS);
    }
    wait(NULL);
    signal(SIGINT, SIG_DFL);
    return (EXIT_SUCCESS);
}
