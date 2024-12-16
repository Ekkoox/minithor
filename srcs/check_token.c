/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:41:58 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/13 22:55:57 by razouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  count_sign(char *value)
{
	int i;
	int sign;

	i = 0;
	sign = 0;
	while(value[i])
	{
		if (value[i] == '$')
			sign++;
		i++;
	}
	return (sign);
}

static void dup_value_expand(char *dup_value, t_token *token, t_env *env, int index)
{
	int i;
	int y;
	int j;

	y = 0;
	i = 0;
	j = 0;
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

static void	expand_plus(t_token *token, t_env *env, int index, char *expand)
{
	int len;
	char *dup_value;

	len = (ft_strlen(token->value) - (ft_strlen(expand) + 1) + ft_strlen(env->value));
	dup_value = ft_strdup(token->value);
	while(env->next && (ft_strcmp(env->type, expand)))
		env = env->next;
	free(token->value);
	token->value = ft_calloc(sizeof(char), len + 1);
	if(token->value == NULL)
		return;
	dup_value_expand(dup_value, token, env, index);
}

static int find_on_env(t_token *token, int index, t_env *env)
{
	char *sup_exp;
	int i;
	int j;

	i = index;
	j = 0;
	while((token->value[i]) && (token->value[i] != ' ' && token->value[i] != '$'))
		i++;
	sup_exp = ft_calloc(sizeof(char), ((i - index) + 1));
	if (!sup_exp)
		return (0);
	while(index < i)
	{
		sup_exp[j] = token->value[index];
		index++;
		j++;
	}
	while(env->next)
	{
		if (ft_strcmp(sup_exp, env->type) == 0)
			return(ft_strlen(sup_exp));
		env = env->next;
	}
	return(0);	
}

static void get_line(t_token *token)
{
	int i;
	char *str;
	int j;

	i = 0;
	j = 0;
	while(token->value[i] && token->value[i] != '$')
		i++;
	str = ft_calloc(sizeof(char), i + 1);
	while(j < i)
	{
		str[j] = token->value[j];
		j++;
	}
	free(token->value);
	token->value = ft_strdup(str);
}

static void	expand_env(t_token *token, t_env *env, int *index)
{
	char *expand;
	int i;
	int len;
	t_env *tmp;

	i = 0;
	tmp = env;
	len = find_on_env(token, *index, env);
	env = tmp;
	if(len == 0)
	{
		get_line(token);
		return;
	}
	expand = ft_calloc(sizeof(char), len + 1);
	while(token->value[*index] != ' '  && token->value[*index] && token->value[*index] != '$')
	{
		expand[i] = token->value[*index];
		i++;
		*index = *index + 1;
	}
	expand[i] = '\0';
	i = *index;
	expand_plus(token, env, i, expand);
}


static void check_file(char *file, char *chevron)
{
	if (ft_strlen(chevron) == 1)
		open(file, O_CREAT | O_WRONLY);
	else
		open(file, O_CREAT | O_APPEND);
}

static void change_le_plan(t_token *token, int index, int start)
{
	int i;
	int len;
	int j;
	char *dup_value;

	i = (index - start);
	j = 0; 
	len = start;
	dup_value = ft_strdup(token->value);
	len = (ft_strlen(token->value) - i);
	free(token->value);
	token->value = ft_calloc(sizeof(char), len + 1);
	while(j < start)
	{
		token->value[j] = dup_value[j];
		j++;
	}
	while(dup_value[index])
	{
		token->value[j] = dup_value[index];
		index++;
		j++;
	}
	token->value[j] = '\0';
	free(dup_value);
}

static int juge_expand(t_token *token, int *index, t_env *env, int *nb_sign)
{
	int i;
	int j;
	char *expand;
	t_env *tmp;

	i = *index + 1;
	j = 0;
	tmp = env;
	while(token->value[i] && (token->value[i] != ' ' && token->value[i] != '$'))
		i++;
	if (i == *index + 1)
		return (0);
	expand = ft_calloc(sizeof(char), i + 1);
	i = *index + 1;
	while(token->value[i] && (token->value[i] != ' ' && token->value[i] != '$'))
	{
		expand[j] = token->value[i];
		i++;
		j++;
	}
	while(env->next)
	{
		if (ft_strcmp(expand, env->type) == 0)
			return(free(expand), 1);
		env = env->next;
	}
	*nb_sign = *nb_sign - 1;
	env = tmp;
	return (free(expand), change_le_plan(token, i, *index), 0);
}

void	check_token(t_token *token, t_env *env)
{
	int i;
	int nb_sign;

	i = 0;
	while(token->next)
	{
		nb_sign = count_sign(token->value);
		while(token->value[i] && nb_sign > 0)
		{	
			if(token->value[i] == '$' && juge_expand(token, &i, env, &nb_sign))
			{
				i++;
				expand_env(token, env, &i);
				nb_sign--;
			}
			if(token->value[i] != '$' && token->value[i])
				i++;
		}
		if (ft_strcmp(token->type, "redirect output") == 0)
		check_file(token->next->value, token->type);
		token = token->next;
		i = 0;
	}
}



