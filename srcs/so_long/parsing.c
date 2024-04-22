/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:40:05 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 18:17:47 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_path(t_map *map)
{
	char	**tab;
	int		i;

	i = 0;
	map->got_coin = 0;
	map->exit = 0;
	tab = malloc(sizeof(char *) * (map->height + 1));
	while (i < map->height)
	{
		tab[i] = ft_strdup(map->data[i]);
		i++;
	}
	tab[i] = 0;
	find_player(map);
	parsing(map, map->y, map->x, tab);
	if (map->got_coin != map->coin || map->exit == 0)
	{
		ft_printf("Invalid Map - Parsing Error\n");
		free_map(tab);
		free_map(map->data);
		exit (1);
	}
	map->got_coin = 0;
	free_map(tab);
}

void	parsing(t_map *map, int y, int x, char **tab)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width
		|| (tab[y][x] != '0' && tab[y][x] != 'C'
		&& tab[y][x] != 'E' && tab[y][x] != 'P'))
		return ;
	if (tab[y][x] == 'C')
		map->got_coin += 1;
	if (tab[y][x] == 'E')
	{
		map->exit = 1;
		return ;
	}
	tab[y][x] = 'F';
	parsing(map, y, x - 1, tab);
	parsing(map, y, x + 1, tab);
	parsing(map, y - 1, x, tab);
	parsing(map, y + 1, x, tab);
}

void	find_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->data[i])
	{
		while (map->data[i][j])
		{
			if (map->data[i][j] == 'P')
			{
				map->y = i;
				map->x = j;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}
