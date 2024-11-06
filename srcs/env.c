/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:17 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/05 19:51:57 by razouani         ###   ########.fr       */
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
	//cree la node PWD puis change la a chaque fois que tu chnage de dossier n'oublie pas de chnager l'ancier PWd
    t_env *env;//change la struct a chaque appel de la fonction
    int i;

    i = 0;
    env = ft_calloc(sizeof(t_env), 1);
    if (!env)
        return (EXIT_FAILURE);
    node_env();
    return (EXIT_SUCCESS);
}