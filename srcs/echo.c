/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:48:28 by enschnei          #+#    #+#             */
/*   Updated: 2025/02/05 22:28:18 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (EXIT_FAILURE);
	if (str[0] == '-' && str[i + 1] == 'n' && ft_strlen(str) == 2)
		return (0);
	return (1);
}

int	ft_echo(t_token *token)
{
	int	flag;

	flag = 0;
	token = token->next;
	while (token->value && token->value[0] == '-' && check_n(token->value) == 0)
	{
		flag = 1;
		token = token->next;
	}
	while (token->next)
	{
		if (ft_strcmp(token->type, "pipe") == 0)
			break ;
		ft_printf("%s", token->value);
		if (token->next->value)
			ft_printf(" ");
		token = token->next;
	}
	if (!flag)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
