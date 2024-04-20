/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:24:38 by allan             #+#    #+#             */
/*   Updated: 2024/04/20 05:37:54 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	handle_inputs(int keysym, t_map *map)
{
	if (keysym == XK_Escape)
	{
		printf("(ESC) END PROGRAM\n");
		free_textures(map, 5);
		free_mlx(map, 1);
		free_map(map);
		exit (1);
	}
	else if (keysym == XK_w)
	{
		if(is_wall_exit(map, map->data[map->y - 1][map->x]) == 0)
			moove_char(map, map->x, map->y - 1);
	}
	else if (keysym == XK_a)
	{
		if(is_wall_exit(map, map->data[map->y][map->x - 1]) == 0)
			moove_char(map, map->x - 1, map->y);
	}
	else if (keysym == XK_s)
	{
		if(is_wall_exit(map, map->data[map->y + 1][map->x]) == 0)
			moove_char(map, map->x, map->y + 1);
	}
	else if (keysym == XK_d)
	{
		if(is_wall_exit(map, map->data[map->y][map->x + 1]) == 0)
			moove_char(map, map->x + 1, map->y);
	}
	printf("position = %c\n", map->data[map->y][map->x]);
	printf("gauche = %c\n", map->data[map->y][map->x - 1]);
	printf("droite = %c\n", map->data[map->y][map->x  + 1]);
	printf("haut = %c\n", map->data[map->y - 1][map->x]);
	printf("bas = %c\n\n", map->data[map->y + 1][map->x]);
	return (0);
}

void	moove_char(t_map *map, int x, int y)
{
	end_game(map, map->data[y][x]);
	mlx_put_image_to_window(map->connection, map->window, 
	map->textures[GROUND_INDEX], map->x * 64, map->y * 64);
	mlx_put_image_to_window(map->connection, map->window, 
	map->textures[CHAR_INDEX], x * 64, y * 64);
	map->y = y;
	map->x = x;
}

bool	is_wall_exit(t_map *map, int c)
{
	if (c == '1')
		return (1);
	else if (c == 'E' && (map->got_coin < map->coin))
		return (1);
	else if (c == 'C')
	{
		map->got_coin++;
		printf("coin = %d/%d\n", map->got_coin, map->coin);
	}
	return (0);
}

void	end_game(t_map *map, int c)
{
	if (c == 'E' && (map->got_coin == map->coin))
	{
		printf("IT'S WIN\n");
		free_textures(map, 5);
		free_mlx(map, 1);
		free_map(map);
		exit (1);
	}
}


