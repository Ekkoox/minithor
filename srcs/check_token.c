/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:41:58 by enschnei          #+#    #+#             */
/*   Updated: 2024/11/08 16:42:01 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_plus(t_token *token, t_env *env, int index, char *expand)
{
	int len;
	int i;
	char *dup_value;
	int j;
	int y;

	len = 0;
	i = 0;
	y = 0;
	j = 0;
	dup_value = ft_strdup(token->value);
	while(env->next && (ft_strcmp(env->type, expand)))
		env = env->next;
	len = (ft_strlen(token->value) - (ft_strlen(expand) + 1) + ft_strlen(env->value));
	free(token->value);
	token->value = ft_calloc(sizeof(char), len + 1);
	//ft_printf("||%s||\n", dup_value);
	while(dup_value[y])
	{
		if (dup_value[y] == '$')
		{
			while(env->value[j])
			{
				token->value[i] = env->value[j];
				i++;
				j++;
			}
			while(y < index)
				y++;
		}
		token->value[i] = dup_value[y];
		i++;
		y++;
	}
	token->value[i] = '\0';
}

static void	expand_env(t_token *token, t_env *env, int *index)
{
	char *expand;
	int i;

	i = 0;
	expand = ft_calloc(sizeof(char), 256);
	while(token->value[*index] != ' ' && token->value[*index])
	{
		expand[i] = token->value[*index];
		i++;
		*index = *index + 1;
	}
	expand[i] = '\0';
	i = *index;
	expand_plus(token, env, i, expand);
}


void	check_token(t_token *token, t_env *env)
{
	int i;

	i = 0;
	while(token->next)
	{
		if (ft_strcmp(token->type, "argument") == 0)
		{
			while(token->value[i])
			{	
				if(token->value[i] == '$')
				{
					i++;
					expand_env(token, env, &i);
				}
				i++;
			}
				
		}
		token = token->next;
	}
}