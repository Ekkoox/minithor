/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizi <zizi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:14:51 by zizi              #+#    #+#             */
/*   Updated: 2025/01/25 14:36:43 by zizi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void    free_node(t_env *target)
{
    free(target->type);
    free(target->value);
    target->type = NULL;
    target->value = NULL;
    free(target);
}

static void    delete_node(t_env *head, t_env *target)
{
    t_env *env;
    t_env *prev;

    env = head;
    prev = NULL;
    while(env->next != target)
        env = env->next;
    prev = env;
    if (target->next != NULL)
    {
        prev->next = target->next;
        free_node(target);
    }
    else
    {
        prev->next = NULL;
        free_node(target);
    }
}

void    ft_unset(t_env *env, t_token *token)
{
    t_token *tmp_token;
    t_env *tmp_env;

    tmp_token = token;
    tmp_env = env;
    token = token->next;
    
    while(ft_strcmp(env->type, token->value) != 0) 
        env = env->next;
    delete_node(tmp_env, env);
    env = tmp_env;
    token = tmp_token;
}