/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:42:24 by enschnei          #+#    #+#             */
/*   Updated: 2023/11/29 15:06:04 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa_base(unsigned int n, char c)
{
	char	*hexa;
	int		len;

	len = 0;
	if (c >= 'a' && c <= 'z')
		hexa = "0123456789abcdef";
	else if (c >= 'A' && c <= 'Z')
		hexa = "0123456789ABCDEF";
	else
		return (0);
	if (n >= 16)
		len += ft_hexa_base(n / 16, c);
	len += ft_putchar(hexa[n % 16]);
	return (len);
}

static int	ft_hexa_base2(uintptr_t n)
{
	char	*hexa;
	int		len;

	len = 0;
	hexa = "0123456789abcdef";
	if (n >= 16)
		len += ft_hexa_base2(n / 16);
	len += ft_putchar(hexa[n % 16]);
	return (len);
}

int	ft_hexa_p(void *ptr)
{
	int	len;

	if (!ptr)
		return (ft_putstr("(nil)"));
	len = ft_putstr("0x") + ft_hexa_base2((uintptr_t)ptr);
	return (len);
}
