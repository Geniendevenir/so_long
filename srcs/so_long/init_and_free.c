/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:43:39 by allan             #+#    #+#             */
/*   Updated: 2024/04/20 00:54:18 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
#include <fcntl.h>

t_map	init_map(char	*argv)
{
	t_map	map;
	char	*line;
	int	fd;
	int	i;
	
	i = 0;
	map.height = 0;
	map.width = 0;
	map.img_size = 0;
	map.got_coin = 0;
	map.coin = 0;
	map.x = 0;
	map.y = 0;
	fd = open(argv, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }
    while ((line = get_next_line(fd)) != NULL) 
	{
		map.height++;
        free(line); // Free memory allocated by get_next_line
    }
	map.data = malloc(sizeof(char *) * (map.height + 1));
	lseek(fd, 0, SEEK_SET);
	while ((line = get_next_line(fd)) != NULL) 
	{
		map.data[i] = ft_strdup(line);
        free(line); // Free memory allocated by get_next_line
		i++;
    }
	map.data[i] = NULL;
    close(fd);
	return (map);
}

bool	init_mlx(t_map *map)
{
	int max_width;
	int	max_heigth;

	max_width = 64 * map->width;
	max_heigth = 64 * map->height;
	printf("width = %d\nheight = %d\n", map->width, map->height);
	printf("max width = %d\nmax height = %d\n", max_width, max_heigth);
	map->connection = mlx_init();
	if (map->connection == NULL)
	{
		free_map(map);
		return (1);
	}
	map->window = mlx_new_window(map->connection, max_width, max_heigth, "So Long");
	if (map->window == NULL)
	{
		free_mlx(map, 0);
		free_map(map);
		return (1);
	}
	return (0);
}

void	free_map(t_map *map)
{
	int		i;

	i = 0;
	while (map->data[i])
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
}

void	free_mlx(t_map *map, bool type)
{
		if (type == 1)
			mlx_destroy_window(map->connection, map->window);
		mlx_destroy_display(map->connection);
		free (map->connection);
}

void	free_textures(t_map *map, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		mlx_destroy_image(map->connection, map->textures[i]);
	free_mlx(map, 1);
	free_map(map);
	exit(1);
}
