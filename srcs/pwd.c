/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:03:20 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/22 18:54:18 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_token *token)
{
    char *tmp;

    tmp = token->value;
    token->value = getcwd(NULL, 0);
    if (!token->value) 
    {
        perror("Erreur pwd");
        return (EXIT_FAILURE);
    }
    ft_putstr_fd(token->value, STDIN_FILENO);
    ft_putstr_fd("\n", STDIN_FILENO);
    free(tmp);
    return (EXIT_SUCCESS);
}
