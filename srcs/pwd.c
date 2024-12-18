/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:03:20 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/18 09:49:01 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_token *token)
{
    token->value = getcwd(NULL, 0);
    if (!token->value) 
    {
        perror("Erreur pwd");
        return (EXIT_FAILURE);
    }
    ft_printf("%s\n", token->value);
    free(token->value);
    token->flag = 1;
    return (EXIT_SUCCESS);
}
