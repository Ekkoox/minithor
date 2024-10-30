/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:48:28 by enschnei          #+#    #+#             */
/*   Updated: 2024/10/28 19:16:31 by enschnei         ###   ########.fr       */
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
		if (str[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
int ft_echo(t_token *token)
{
    int flag;
    int i;

    flag = 0;
    i = 0;
    token = token->next;
    while(token->next && token->value[0] == '-' && check_n(token->value + 1))
    {
        flag = 1;
        token = token->next;
    }
    while(token->next)
    {
        ft_printf("mon echo = %s", token->value);
        token = token->next;
    }
    if (!flag)
        printf("\n");
    return (EXIT_SUCCESS);
}
