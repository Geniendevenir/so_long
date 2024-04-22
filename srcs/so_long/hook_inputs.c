/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:24:38 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 14:50:49 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_inputs(int keysym, t_map *map)
{
	escape_window(keysym, map);
	if (keysym == XK_w)
	{
		if (is_wall_exit(map, &map->data[map->y - 1][map->x]) == 0)
			moove_player(map, map->x, map->y - 1);
	}
	else if (keysym == XK_a)
	{
		if (is_wall_exit(map, &map->data[map->y][map->x - 1]) == 0)
			moove_player(map, map->x - 1, map->y);
	}
	else if (keysym == XK_s)
	{
		if (is_wall_exit(map, &map->data[map->y + 1][map->x]) == 0)
			moove_player(map, map->x, map->y + 1);
	}
	else if (keysym == XK_d)
	{
		if (is_wall_exit(map, &map->data[map->y][map->x + 1]) == 0)
			moove_player(map, map->x + 1, map->y);
	}
	return (0);
}

bool	is_wall_exit(t_map *map, char *c)
{
	if (*c == '1')
		return (1);
	else if (*c == 'E' && (map->got_coin < map->coin))
		return (1);
	else if (*c == 'C')
	{
		*c = '0';
		map->got_coin++;
		ft_printf("coin = %d/%d\n", map->got_coin, map->coin);
	}
	return (0);
}

void	moove_player(t_map *map, int x, int y)
{
	end_game(map, map->data[y][x]);
	map->moove++;
	ft_printf("Nombre de pas = %d\n", map->moove);
	mlx_put_image_to_window(map->connection, map->window,
		map->textures[GROUND_INDEX], map->x * 64, map->y * 64);
	mlx_put_image_to_window(map->connection, map->window,
		map->textures[CHAR_INDEX], x * 64, y * 64);
	map->y = y;
	map->x = x;
}

void	end_game(t_map *map, int c)
{
	if (c == 'E' && (map->got_coin == map->coin))
	{
		ft_printf("\n\n***************IT'S WIN***************\n\n");
		ft_printf("You won in %d steps\n", map->moove);
		free_textures(map, 5);
		free_mlx(map, 1);
		free_map(map->data);
		exit (1);
	}
}
