/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:41:58 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/03 17:51:26 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void dup_value_expand(char *dup_value, t_token *token, t_env *env, int index)
// {
// 	int i;
// 	int y;
// 	int j;

// 	y = 0;
// 	i = 0;
// 	j = 0;
// 	while(dup_value[y])
// 	{
// 		if (dup_value[y] == '$')
// 		{
// 			while(env->value[j])
// 			{
// 				token->value[i] = env->value[j];
// 				i++;
// 				j++;
// 			}
// 			while(y < index)
// 				y++;
// 		}
// 		token->value[i] = dup_value[y];
// 		i++;
// 		y++;
// 	}
// 	token->value[i] = '\0';
// }

// static void	expand_plus(t_token *token, t_env *env, int index, char *expand)
// {
// 	int len;
// 	char *dup_value;

// 	len = (ft_strlen(token->value) - (ft_strlen(expand) + 1) + ft_strlen(env->value));
// 	dup_value = ft_strdup(token->value);
// 	while(env->next && (ft_strcmp(env->type, expand)))
// 		env = env->next;
// 	free(token->value);
// 	token->value = ft_calloc(sizeof(char), len + 1);
// 	if(token->value == NULL)
// 		return;
// 	dup_value_expand(dup_value, token, env, index);
// }

// static int find_on_env(t_token *token, int index, t_env *env)
// {
// 	char sup_exp;
// 	int i;
// 	int len;

// 	i = index;
// 	while(token->value[i] != ' ' && token->value[i])
// 		i++;
// 	len = (i - index);
// 	sup_exp = ft_calloc(sizeof(char), ((i - index) + 1));
// 	if (len <= 0 || !sup_exp)
// 	while(index < i)
// 	{
		
// 		index++;
// 	}
// 	while((ft_strcmp(sup_exp, env->type) == 0) && env->next)
// 	{
// 		if (ft_strcmp(sup_exp, env->type) == 1)
// 			return()
// 		env = env->next;
// 	}
		
// }

// static void	expand_env(t_token *token, t_env *env, int *index)
// {
// 	char *expand;
// 	int i;
// 	int len;

// 	i = 0;
// 	len = find_on_env(token, *index, env);
// 	if(len == 0)
// 	{
		
// 	}
// 	expand = ft_calloc(sizeof(char), );
// 	while(token->value[*index] != ' ' && token->value[*index])
// 	{
// 		expand[i] = token->value[*index];
// 		i++;
// 		*index = *index + 1;
// 	}
// 	expand[i] = '\0';
// 	i = *index;
// 	expand_plus(token, env, i, expand);
// }


// static void check_file(char *file, char *chevron)
// {
// 	if (ft_strlen(chevron) == 1)
// 		open(file, O_CREAT | O_WRONLY);
// 	else
// 		open(file, O_CREAT | O_APPEND);
// }

// void	check_token(t_token *token, t_env *env)
// {
// 	int i;

// 	i = 0;
// 	while(token->next)
// 	{
// 		if (ft_strcmp(token->type, "argument") == 0){
// 			while(token->value[i]){	
// 				if(token->value[i] == '$'){
// 					i++;
// 					expand_env(token, env, &i);
// 				}
// 				i++;
// 			}	
// 		}
// 		if (ft_strcmp(token->type, "redirect output") == 0)
// 			check_file(token->next->value, token->type);
// 		token = token->next;
// 	}
// }