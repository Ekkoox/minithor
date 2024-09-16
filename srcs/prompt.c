/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:01 by enschnei          #+#    #+#             */
/*   Updated: 2024/09/16 22:17:01 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	creat_the_prompt(void)
{
	char *buffer;
	size_t buf_size;

	buf_size = BUFFER_SIZE;

	// alloc buffer qui stockera la commande entree par l'user
	buffer = (char *)ft_calloc(sizeof(char), buf_size);
	if (buffer == NULL)
	{
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(">", 1);
	// lecture de STDIN en boucle
	while (getline(&buffer, &buf_size, stdin) > 0)
	{
		ft_printf("cmd = %s\n", buffer);
		ft_putstr_fd(">", 1);
	}
	free(buffer);
	return (EXIT_SUCCESS);
}
