/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:43:10 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/23 16:16:52 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void update_env_list(t_env *env)
{
	t_env *tmp;
	int flag;
	char *oldone;
	
	tmp = env;
	flag = 0;
	while(env->next)
	{
		if (ft_strcmp(env->type, "PWD") == 0)
		{
			oldone = ft_strdup(env->value);
			if (!oldone)
				return ;
			if(flag == 1)
			{
				free(env->value);
				env->value = NULL;
				env->value = getcwd(env->value, 1000);
			}
		}
		if(ft_strcmp(env->type, "OLDPWD") == 0 && (flag == 0))
		{
			free(env->value);
			env->value = oldone;
			oldone = NULL;
			env = tmp;
			flag = 1;
		}
		env = env->next;
	}
	free(oldone);
	env = tmp;
}

int ft_cd(t_token *token, t_env *env) 
{ 
    token = token->next;
    if (chdir(token->value) == -1) 
    {
        ft_printf("bash: cd: %s: No such file or directory\n", token->value);
		var_g = 1;
        return (EXIT_FAILURE);	
    }
	update_env_list(env);
    return (EXIT_SUCCESS);
}