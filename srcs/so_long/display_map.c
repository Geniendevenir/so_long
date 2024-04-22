/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 03:29:58 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 14:50:29 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_mlx(t_map *map)
{
	int	max_width;
	int	max_heigth;

	max_width = 64 * map->width;
	max_heigth = 64 * map->height;
	map->connection = mlx_init();
	if (map->connection == NULL)
	{
		free_map(map->data);
		return (1);
	}
	map->window = mlx_new_window(map->connection, max_width,
			max_heigth, "So Long");
	if (map->window == NULL)
	{
		free_mlx(map, 0);
		free_map(map->data);
		return (1);
	}
	return (0);
}

void	display_map(t_map *map)
{
	int	width;
	int	height;

	init_textures(map);
	width = -1;
	while (++width < map->width)
	{
		height = -1;
		while (++height < map->height)
		{
			select_texture(map, map->data[height][width], width, height);
		}
	}
}

void	init_textures(t_map *map)
{
	map->textures[WALL_INDEX] = check_textures(map, WALL_PATH, 0);
	map->textures[GROUND_INDEX] = check_textures(map, GROUND_PATH, 1);
	map->textures[CHAR_INDEX] = check_textures(map, CHAR_PATH, 2);
	map->textures[COIN_INDEX] = check_textures(map, COIN_PATH, 3);
	map->textures[EXIT_INDEX] = check_textures(map, EXIT_PATH, 4);
}

void	*check_textures(t_map *map, char *path, int index)
{
	void	*texture;

	texture = mlx_xpm_file_to_image(map->connection,
			path, &map->img_size, &map->img_size);
	if (!texture)
		free_textures(map, index);
	return (texture);
}

void	select_texture(t_map *map, char texture, int width, int height)
{
	if (texture == '1')
		mlx_put_image_to_window(map->connection, map->window,
			map->textures[WALL_INDEX], width * 64, height * 64);
	else if (texture == '0')
		mlx_put_image_to_window(map->connection, map->window,
			map->textures[GROUND_INDEX], width * 64, height * 64);
	else if (texture == 'P')
	{
		mlx_put_image_to_window(map->connection, map->window,
			map->textures[CHAR_INDEX], width * 64, height * 64);
		map->x = width;
		map->y = height;
	}
	else if (texture == 'C')
		mlx_put_image_to_window(map->connection, map->window,
			map->textures[COIN_INDEX], width * 64, height * 64);
	else if (texture == 'E')
		mlx_put_image_to_window(map->connection, map->window,
			map->textures[EXIT_INDEX], width * 64, height * 64);
}
