/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:05:21 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/31 19:23:27 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_permissions(char *path)
{
    if (access(path, F_OK) != 0)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        exit(127);
    }
    if (access(path, X_OK) != 0)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": Permission denied\n", 2);
        exit(126);
    }
}

static int error_directory(t_minishell *minishell, int *index)
{
    int i;
    
    i = *index;
    if (strspn(minishell->buffer + i, "/") == ft_strlen(minishell->buffer + i)) // coder strspn
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(minishell->buffer + i, 2);
        ft_putstr_fd(": Is a directory\n", 2);
        g_var = 126;
        return (EXIT_FAILURE);
    }
    if (ft_strncmp(minishell->buffer + i, "/.", 2) == 0) 
    {
        int j = i + 2;
        while (minishell->buffer[j] == '/' || (minishell->buffer[j] == '.' && minishell->buffer[j - 1] == '/'))
            j++;

        if (minishell->buffer[j] == '\0')
        {
            ft_putstr_fd("bash: ", 2);
            ft_putstr_fd(minishell->buffer + i, 2);
            ft_putstr_fd(": Is a directory\n", 2);
            g_var = 126;
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}


int check_error(t_minishell *minishell, int *index)
{
    if (error_directory(minishell, index) == 1)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
