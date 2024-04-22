/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:56:04 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 13:22:45 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		destlen;
	int		i;

	i = 0;
	destlen = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (destlen + 1));
	if (!dest)
		return (NULL);
	while (*(s1 + i))
	{
		*(dest + i) = *(s1 + i);
		i++;
	}
	while (*s2)
	{
		*(dest + i) = *s2++;
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}
