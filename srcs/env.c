/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:17 by enschnei          #+#    #+#             */
/*   Updated: 2024/10/29 18:45:15 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_token *token)
{
    int i;

    i = 0;
    while(token->value)
    {
        ft_printf("%s\n", token->value);
        token = token->next;
    }
    return (EXIT_SUCCESS);
}