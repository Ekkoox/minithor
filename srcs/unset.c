/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:14:51 by enschnei          #+#    #+#             */
/*   Updated: 2025/02/09 01:37:30 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_env *target)
{
	free(target->type);
	free(target->value);
	target->type = NULL;
	target->value = NULL;
	free(target);
}

static void	delete_node(t_env *head, t_env *target)
{
	t_env	*env;
	t_env	*prev;

	env = head;
	prev = NULL;
	while (env->next != target)
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

static int find_the_thing_env(t_env *env, char *thing)
{
	t_env *tmp;

	tmp = env;
	while(env->next)
	{
		if (ft_strcmp(env->type, thing) == 0)
		{
			env = tmp;
			return (0);
		}
		env = env->next;
	}
	env = tmp;
	return (1);
}
static int what_i_do(t_minishell *minishell, t_token *token, t_env *tmp_env)
{
	t_env *target;

	if (find_the_thing_env(minishell->env, token->value) == 0)
		{
			if (ft_strcmp(minishell->env->type, token->value) == 0)
			{
				target = minishell->env;
				minishell->env = minishell->env->next;
				tmp_env = tmp_env->next;
				free_node(target);
				return (0);
			}
			else
			{   
				while(ft_strcmp(minishell->env->type, token->value) != 0) 
					minishell->env =  minishell->env->next;
				delete_node(tmp_env,  minishell->env);
				return (1);
			}   
		}
		return (0);
}

void    ft_unset(t_minishell *minishell, t_token *token)
{
	t_token *tmp_token;
	t_env *tmp_env;

    tmp_token = token;
    tmp_env = minishell->env;
    token = token->next;
	int i = 0;
	while(token->value)
	{	
		i++;
		if(what_i_do(minishell, token, tmp_env) == 1)
			minishell->env = tmp_env;
		token = token->next;
	}
	token = tmp_token;
}
