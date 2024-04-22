/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:36:37 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 14:50:08 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_mlx(t_map *map, bool type)
{
	if (type == 1)
		mlx_destroy_window(map->connection, map->window);
	mlx_destroy_display(map->connection);
	free(map->connection);
}

void	free_textures(t_map *map, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		mlx_destroy_image(map->connection, map->textures[i]);
	free_mlx(map, 1);
	free_map(map->data);
	exit(1);
}

void	escape_window(int keysym, t_map *map)
{
	if (keysym == XK_Escape)
	{
		printf("(ESC) END PROGRAM\n");
		free_textures(map, 5);
		free_mlx(map, 1);
		free_map(map->data);
		exit (1);
	}
}

int	close_window(t_map *map)
{
	ft_printf("CLOSE WINDOW - END PROGRAM\n");
	free_textures(map, 5);
	free_mlx(map, 1);
	free_map(map->data);
	exit (1);
}
