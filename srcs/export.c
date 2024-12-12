/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:53:35 by razouani          #+#    #+#             */
/*   Updated: 2024/12/09 18:29:20 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void get_type_env(t_env * env, t_token *token)
{
	int i;

	i = 0;
	token = token->next;
	while(token->value[i] != '=')
		i++;
	env->type = ft_calloc(sizeof(char), i + 1);
	
}

void ft_export(t_env *env, t_token *token)
{
	t_env *tmp;
	t_token *tmp1;
	
	tmp = env;
	tmp1 = token;
	
	while(env->next)
		env = env->next;
	env->next = ft_calloc(sizeof(t_env), 1);
	env = env->next;
	get_type_env(env, token);
}