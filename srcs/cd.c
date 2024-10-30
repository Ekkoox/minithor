/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:43:10 by enschnei          #+#    #+#             */
/*   Updated: 2024/10/28 20:01:13 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(t_token *token) 
{ 
    token = token->next;
    if (chdir(token->next->value) == -1) 
    {
        perror("cd error");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
