/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 03:34:03 by allan             #+#    #+#             */
/*   Updated: 2024/04/20 05:36:11 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
#include <fcntl.h>

void	print_map(t_map *map)
{
	int	i;
	
	i = 0;
	while (map->data[i])
	{
		printf("%s", map->data[i]);
		i++;
	}
}

int main(int argc, char **argv) {
	t_map	map;
	
	if (argc != 2)
		return (1);
	map = init_map(argv[1]);
	if (map.data == NULL)
		return (write(1, "Map Init Error\n", 15));
	print_map(&map);
	if (check_map(&map) == 1)
	{
		free_map(&map);
		return (write(1, "Map Data Error\n", 15));
	}
	if (init_mlx(&map) == 1)
		return (write(1, "Mlx Init Error\n", 15));
	/* printf("width = %d\nheight = %d\n", map.width, map.height); */
	int save_coin = map.coin;
	display_map(&map);
	map.coin = save_coin;
	printf("init got_coin = %d\n", map.got_coin);
	mlx_key_hook(map.window, handle_inputs, &map);
	mlx_loop(map.connection);
	free_map(&map);
    return 0;
}


