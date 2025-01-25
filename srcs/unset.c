/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizi <zizi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:14:51 by zizi              #+#    #+#             */
/*   Updated: 2025/01/25 13:20:55 by zizi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    ft_unset(t_env *env, t_token *token)
{
    t_token *tmp_token;
    t_env *tmp_env;

    tmp_token = token;
    tmp_env = env;
    token = token->next;
    
    while(ft_strcmp(env->type, token->value) != 0) 
        env = env->next;
    delete_node(tmp_env, env, token->value)
}