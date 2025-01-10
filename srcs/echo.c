/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:48:28 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/09 18:21:38 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_n(char *str)
{  
	int	i;

	i = 0;
	if (!str[i])
		return (EXIT_FAILURE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (EXIT_FAILURE);
        i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_echo(t_token *token)
{
	int flag;

	flag = 0;
    token = token->next;
	while (token->value && token->value[0] == '-' && check_n(token->value))
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
