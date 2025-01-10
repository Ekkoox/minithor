/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:03:20 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/10 20:02:43 by enschnei         ###   ########.fr       */
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
   // free(token->value);
    return (EXIT_SUCCESS);
}
