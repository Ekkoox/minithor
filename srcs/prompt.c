/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/16 21:47:57 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int creat_the_prompt(int fd)
{
	char buffer[BUFFER_SIZE];
	int read_line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (EXIT_FAILURE);
	while (1)
	{
		read_line = read (fd, buffer, BUFFER_SIZE);
	}
	return (EXIT_SUCCESS);
}