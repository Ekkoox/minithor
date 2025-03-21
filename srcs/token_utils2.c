/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:59:42 by enschnei          #+#    #+#             */
/*   Updated: 2025/03/19 17:34:54 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char *str, int *index)
{
	int	i;

	i = *index;
	
	if (!str[i])
		return (1);
	else if (str[i] == ' ')
		return(0);
	else if(str[i] == '|')
		return(0);
	else if(str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (-1);
		return(0);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (-1);
		return(0);
	}
	return (1);
}

int	count_quote(char *mot)
{
	int		i;
	int		c;
	char	chef;

	i = 0;
	c = 0;
	chef = 0;
	if (!mot)
		return(0);
	while (mot[i])
	{
		if ((mot[i] == '"' || mot[i] == '\'') && (c == 0))
			chef = mot[i];
		if (mot[i] == chef)
			c++;
		i++;
	}
	return (c);
}

char	*in_quote(char *mot, int quote)
{
	int		i;
	int		y;
	char	*clear_word;
	char	cot;

	i = 0;
	y = 0;
	cot = mot[i];
	clear_word = ft_calloc(sizeof(char), (ft_strlen(mot) - quote) + 1);
	if (!clear_word)
		return (NULL);
	while (mot[i])
	{
		if (mot[i] == cot)
			i++;
		clear_word[y] = mot[i];
		i++;
		y++;
	}
	clear_word[y] = '\0';
	return (clear_word);
}

static void not_the_same(int *index, int *index_dest, char *buffer, char *dest)
{
	while ((buffer[*index] != 34 || buffer[*index] != 39) && (buffer[*index]))
		{
			if(buffer[*index] == 34 || buffer[*index] == 39)
				*index += 1;
			else 
			{
				dest[*index_dest] = buffer[*index];
				*index += 1;
				*index_dest += 1;
			}
		}
		buffer[*index] = '\0';
}

static int another_word(char *buffer, int *index)
{
	int i;

	i = *index;
	while(buffer[i])
	{
		if (buffer[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	clear_quote(char *buffer, char *dest, int *index, int start,
		int *index_dest)
{
	int	i;

	i = 0;
	if (start == *index)
	{
		*index += 1;
		while (buffer[*index] && ((buffer[*index] != 34) || (buffer[*index] != 39)))
		{
			ft_printf("%c\n", buffer[*index]);
			if ((buffer[*index] == 34 || buffer[*index] == 39) && (buffer[*index + 1] == ' ') && (another_word(buffer, index)))
			{
				ft_printf("CACA\n");
				*index += 1;
				break;
			}
			else if ((buffer[*index] == 34 || buffer[*index] == 39) && (buffer[*index + 1] != ' '))
					*index += 1;
			dest[i] = buffer[*index];
			i++;
			if(buffer[*index + 1] != '\0')
				*index += 1;
		}
		dest[i] = '\0';
		//ft_printf("%s\n", dest);
	}
	else
		not_the_same(index, index_dest, buffer, dest);
	return ;
}


