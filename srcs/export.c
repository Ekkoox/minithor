/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizi <zizi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:53:35 by razouani          #+#    #+#             */
/*   Updated: 2025/01/25 14:38:56 by zizi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_type_env(t_token *token)
{
	int i;
	int j;
	char *res;

	i = 0;
	j = 0;
	token = token->next;
	while(token->value[i] != '=')
		i++;
	res = ft_calloc(sizeof(char), i);
	while(token->value[i] && i > j)
	{
		res[j] = token->value[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

static void get_value_env(t_env *env, t_token *token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	token = token->next;
	if(env->value)
	{
		free(env->value);
		env->value = NULL;
	}
	while(token->value[i] != '=' && token->value[i])
		i++;
	env->value = ft_calloc(sizeof(char), (ft_strlen(token->value) - i) + 1);
	i++;
	while(token->value[i])
	{
		env->value[j] = token->value[i];
		i++;
		j++;
	}
	env->value[j] = '\0';
}

int ft_export(t_env *env, t_token *token)
{
	t_env *tmp;
	t_token *tmp1;
	char *type;
	
	tmp = env;
	tmp1 = token;
	type = get_type_env(token);
	token = tmp1;
	while(env->next->type){
		env = env->next;
	}
	if (ft_strcmp(env->type, type) != 0)
	{
		env = env->next;
		env->type = ft_strdup(type);
		env->next = ft_calloc(sizeof(t_env), 1);
	}
	get_value_env(env, token);
	token->flag = 1;
	env = tmp;
	return (EXIT_SUCCESS);
}
