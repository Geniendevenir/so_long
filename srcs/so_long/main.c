/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 03:34:03 by allan             #+#    #+#             */
/*   Updated: 2024/04/22 14:48:41 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../libft/inc/libft.h"
#include "../libft/inc/get_next_line.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (1);
	map = init_map(argv[1]);
	if (map.data == NULL)
		return (write(1, "Map Init Error\n", 15));
	if (check_map(&map) == 1)
	{
		free_map(map.data);
		return (write(1, "Map Data Error\n", 15));
	}
	check_path(&map);
	if (init_mlx(&map) == 1)
		return (write(1, "Mlx Init Error\n", 15));
	display_map(&map);
	mlx_key_hook(map.window, handle_inputs, &map);
	mlx_hook(map.window, 17, 0, close_window, &map);
	mlx_loop(map.connection);
	return (0);
}
