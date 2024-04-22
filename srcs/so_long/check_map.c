/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:41:46 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 12:51:42 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_map(t_map *map)
{
	int		i;

	i = 0;
	map->character = 0;
	map->exit = 0;
	map->coin = 0;
	while (map->data[0][++i])
		map->width++;
	if (map->width == map->height || map->width < 4
		|| map->height < 4 || map->width > 30 || map->height > 16)
		return (1);
	i = 0;
	while (map->data[i])
	{
		if (check_oblong(map->data[i], map->width))
			return (1);
		if (check_doubles(map->data[i], map))
			return (1);
		i++;
	}
	if (check_wall(map))
		return (1);
	if (map->character == 0 || map->exit == 0 || map->coin == 0)
		return (1);
	return (0);
}

bool	check_oblong(char *line, int width)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'P' && line[i] != 'C'
			&& line[i] != 'E' && line[i] != '\n')
			return (1);
		if (line[i] == '\n' && i != width)
			return (1);
		i++;
	}
	if (i - 1 != width)
		return (1);
	return (0);
}

bool	check_doubles(char *line, t_map *map)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'P' && map->character == 1)
			return (1);
		else if (line[i] == 'P')
			map->character = 1;
		else if (line[i] == 'E' && map->exit == 1)
			return (1);
		else if (line[i] == 'E')
			map->exit = 1;
		else if (line[i] == 'C')
			map->coin++;
		i++;
	}
	return (0);
}

bool	check_wall(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map->data[i])
	{
		while (map->data[i][j])
		{
			if (map->data[i][0] != '1'
				|| map->data[i][map->width - 1] != '1')
				return (1);
			if ((i == 0 || i == map->height - 1)
				&& map->data[i][j] != '1' && map->data[i][j] != '\n')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
