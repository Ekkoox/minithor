/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:58:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/02/03 18:42:26 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	int i;

    i = 0;
	while (s[i]) 
    {
		if (ft_strchr(accept, s[i]) == 0)	
            break;
        i++;
	}
	return (i);
}
