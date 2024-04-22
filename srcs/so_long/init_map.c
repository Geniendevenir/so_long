/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:43:39 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 18:36:34 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../libft/inc/libft.h"
#include "../libft/inc/get_next_line.h"
#include <fcntl.h>

t_map	init_map(char	*argv)
{
	t_map	map;
	int		fd;

	init_value(&map);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	map = create_map(map, fd);
	close(fd);
	return (map);
}

void	init_value(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->img_size = 0;
	map->got_coin = 0;
	map->coin = 0;
	map->x = 0;
	map->y = 0;
	map->moove = 0;
}

t_map	create_map(t_map map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map.height++;
		free(line);
	}
	map.data = malloc(sizeof(char *) * (map.height + 1));
	lseek(fd, 0, SEEK_SET);
	while (i < map.height)
	{
		line = get_next_line(fd);
		map.data[i] = ft_strdup(line);
		free(line);
		i++;
	}
	line = get_next_line(fd);
	free(line);
	map.data[i] = NULL;
	return (map);
}

/* void	print_map(char **map)
{
	int		i;
	
	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
} */
