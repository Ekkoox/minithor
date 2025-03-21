/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:05:21 by enschnei          #+#    #+#             */
/*   Updated: 2025/03/19 22:10:22 by roane            ###   ########.fr       */
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

static int error_directory(t_token *token)
{
    t_token *tmp;
    int j;
    
    tmp = token;
    j = 2;
    while (token)
    {
        if (!token->value)
        {
            token = token->next;
            continue;
        }
        // if (ft_strncmp(token->value, "/", 1) == 0)
        // {
        //     ft_putstr_fd("bash: ", 2);
        //     ft_putstr_fd(token->value, 2);
        //     ft_putstr_fd(": Is a directory\n", 2);
        //     g_var = 126;
        //     return (EXIT_FAILURE);
        // }
        if (ft_strncmp(token->value, "/.", 2) == 0)
        {
            while (token->value[j] == '/' || (token->value[j] == '.' && token->value[j - 1] == '/'))
                j++;
            if (token->value[j] == '\0')    
            {
                ft_putstr_fd("bash: ", 2);
                ft_putstr_fd(token->value, 2);
                ft_putstr_fd(": Is a directory\n", 2);
                g_var = 126;
                return (EXIT_FAILURE);
            }
        }
        j = 0;
        while (token->value[j] == '/')
            j++;
        if (token->value[j] == '\0') // Si on est à la fin de la chaîne, c'est un dossier
        {
            ft_putstr_fd("bash: ", 2);
            ft_putstr_fd(token->value, 2);
            ft_putstr_fd(": Is a directory\n", 2);
            g_var = 126;
            return (EXIT_FAILURE);
        }
        token = token->next;
    }
    token = tmp;
    return (EXIT_SUCCESS);
}

int check_error(t_token *token)
{
    if (error_directory(token) == 1)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
