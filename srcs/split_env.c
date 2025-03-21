/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:16:19 by enschnei          #+#    #+#             */
/*   Updated: 2025/03/19 22:11:56 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*ft_strndup(const char *str, int index, int n)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(sizeof(char) * (n + 1));
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

char	**ft_split_env(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;
	int len;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * 3);
	if (!tab || !s)
		return (free(tab), NULL);
	if (s[i] != '\0')
	{
		len = count_char(s, c, i);
		tab[j++] = ft_strndup(s, i, len);
		i += len;
		if (s[i] == c)
			i++;
		if (s[i] != '\0')
			tab[j++] = ft_strndup(s, i, count_char(s, '\0', i));
	}
	tab[j] = NULL;
	return (tab);
}
