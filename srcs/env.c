/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:17 by enschnei          #+#    #+#             */
/*   Updated: 2025/02/09 01:06:00 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->env;
	while (minishell->env->next)
	{
		ft_printf("%s", minishell->env->type);
		ft_printf("%c", '=');
		ft_printf("%s\n", minishell->env->value);
		minishell->env = minishell->env->next;
	}
	minishell->env = tmp;
	return (EXIT_SUCCESS);
}
