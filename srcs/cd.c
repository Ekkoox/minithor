/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:43:10 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/31 15:26:46 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_env *env, char **oldone, int *flag)
{
	if (ft_strcmp(env->type, "PWD") == 0)
	{
		*oldone = ft_strdup(env->value);
		if (!(*oldone))
			return ;
		if (*flag == 1)
		{
			free(env->value);
			env->value = NULL;
			env->value = getcwd(NULL, 1000);
		}
	}
}

static void	update_oldpwd(t_env *env, char **oldone, int *flag, t_env *tmp)
{
	if (ft_strcmp(env->type, "OLDPWD") == 0 && (*flag == 0))
	{
		free(env->value);
		env->value = *oldone;
		*oldone = NULL;
		env = tmp;
		*flag = 1;
	}
}

static void	update_env_list(t_env *env)
{
	t_env	*tmp;
	int		flag;
	char	*oldone;

	tmp = env;
	flag = 0;
	oldone = NULL;
	while (env->next)
	{
		update_pwd(env, &oldone, &flag);
		update_oldpwd(env, &oldone, &flag, tmp);
		env = env->next;
	}
	free(oldone);
	env = tmp;
}

int	ft_cd(t_token *token, t_env *env)
{
	token = token->next;
	if (chdir(token->value) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_var = 1;
		return (EXIT_FAILURE);
	}
	update_env_list(env);
	return (EXIT_SUCCESS);
}
