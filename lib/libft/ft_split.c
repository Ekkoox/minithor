/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:30:51 by enschnei          #+#    #+#             */
/*   Updated: 2024/01/26 15:18:12 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(const char *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *str, int index, int n)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(sizeof(char) * n + 1);
	if (!s)
		return (NULL);
	while (str[index] && i < n)
	{
		s[i] = str[index];
		i++;
		index++;
	}
	s[i] = '\0';
	return (s);
}

void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab || !s)
		return (free(tab), NULL);
	while (j < count_words(s, c) && s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_strndup(s, i, count_char(s, c, i));
			if (!(tab[j]))
				return (ft_free(tab, j));
			while (s[i] != c && s[i])
				i++;
			j++;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}
