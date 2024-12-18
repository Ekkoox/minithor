/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razouani <razouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:43:10 by enschnei          #+#    #+#             */
/*   Updated: 2024/12/18 14:35:01 by razouani         ###   ########.fr       */
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
			if(flag == 1){
				free(env->value);
				env->value = NULL;
				env->value = getcwd(env->value, 1000);
			}
		}
		if(ft_strcmp(env->type, "OLDPWD") == 0 && (flag == 0)){
			env->value = oldone;
			env = tmp;
			flag = 1;
		}
		env = env->next;
	}
	env = tmp;
}

int ft_cd(t_token *token, t_env *env) 
{ 
    token = token->next;
    if (chdir(token->value) == -1) 
    {
        perror("cd error");
        return (EXIT_FAILURE);
    }
	update_env_list(env);
    return (EXIT_SUCCESS);
}