/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:40:05 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 03:32:55 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void  check_path(t_map *map)
{
	int		coin;
	bool	map_exit;
	char	**tab;
	int		i;

	i = 0;
	coin = 0;
	map_exit = 0;
	tab = malloc(sizeof(char *) * (map->height + 1));
	while (i < map->height)
	{
		tab[i] = ft_strdup(map->data[i]);
		i++;
	}
	tab[i] = 0;
	find_player(map);
	parsing(map, map->y, map->x, tab, &coin, &map_exit);
	if (coin != map->coin || map_exit == 0)
	{
		ft_printf("Parsing Error\n");
		free_tab(tab);
		free_map(map);
		exit (1);
	}
	free_tab(tab);
}

void	parsing(t_map *map, int y, int x, char **tab, int *coin, bool *exit)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width || 
	(tab[y][x] != '0' && tab[y][x] != 'C' && tab[y][x] != 'E' && 
		tab[y][x] != 'P'))
		return ;
	if (tab[y][x] == 'C')
		*coin += 1;
	if (tab[y][x] == 'E')
		*exit = 1;
	tab[y][x] = 'F';
	parsing(map, y, x - 1, tab, coin, exit);
	parsing(map, y, x + 1, tab, coin, exit);
	parsing(map, y - 1, x, tab, coin, exit);
	parsing(map, y + 1, x, tab, coin, exit);
}

void	find_player(t_map *map)
{
	int i = 0;
	int j = 0;

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