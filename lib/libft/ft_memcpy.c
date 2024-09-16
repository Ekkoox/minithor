/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/11/17 18:22:46 by enschnei          #+#    #+#             */
/*   Updated: 2023/11/17 18:22:46 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t		i;
	const char	*src;
	char		*dest;

	i = 0;
	src = source;
	dest = destination;
	if (size >= 0 && !src && !dest)
		return (dest);
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
