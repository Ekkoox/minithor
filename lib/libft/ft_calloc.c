/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:04:40 by enschnei          #+#    #+#             */
/*   Updated: 2023/11/17 18:04:40 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((nmemb * size) < nmemb || (nmemb * size) < size)
		return (NULL);
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (tmp);
	ft_bzero(tmp, (nmemb * size));
	return (tmp);
}
