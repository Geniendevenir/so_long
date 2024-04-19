/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:07:06 by adebert           #+#    #+#             */
/*   Updated: 2024/04/15 21:00:32 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdbool.h>

void	ft_free(char**split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	count_word(char *str, char sep)
{
	int		words_nbr;
	bool	inside_word;

	words_nbr = 0;
	while (*str)
	{
		inside_word = false;
		while (*str == sep && *str)
			++str;
		while (*str != sep && *str)
		{
			if (!inside_word)
			{
				words_nbr++;
				inside_word = true;
			}
			++str;
		}
	}
	return (words_nbr);
}

char	*get_next_word(char *str, char sep)
{
	static int	cursor = 0;
	char		*word;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (str[cursor] == sep)
		++cursor;
	while ((str[cursor + len] != sep) && str[cursor + len])
		++len;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while ((str[cursor] != sep) && str[cursor])
		word[i++] = str[cursor++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char sep)
{
	int		words_nbr;
	char	**tab;
	int		i;

	i = 0;
	words_nbr = count_word(str, sep);
	if (!words_nbr)
		exit(1);
	tab = malloc(sizeof(char *) * (words_nbr + 2));
	if (!tab)
		return (NULL);
	while (words_nbr-- >= 0)
	{
		if (i == 0)
		{
			tab[0] = malloc(sizeof(char));
			if (!tab[0])
				return (NULL);
			tab[i++][0] = '\0';
			continue ;
		}
		tab[i++] = get_next_word(str, sep);
	}
	tab[i] = NULL;
	return (tab);
}
