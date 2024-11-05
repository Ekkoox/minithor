/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:17 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/05 19:20:54 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int node_env(t_env *env)
{
    while()
    {
        
    }
    return (EXIT_SUCCESS);
}

int ft_env(t_token *token, char **ev)
{
    t_env *env;
    int i;

    i = 0;
    env = ft_calloc(sizeof(t_env), 1);
    if (!env)
        return (EXIT_FAILURE);
    node_env();
    return (EXIT_SUCCESS);
}