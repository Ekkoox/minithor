/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:05:21 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/29 17:44:54 by enschnei         ###   ########.fr       */
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
