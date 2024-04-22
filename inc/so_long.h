/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:25:25 by adebert           #+#    #+#             */
/*   Updated: 2024/04/22 03:41:42 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define WALL_PATH "srcs/textures/WALL.xpm"
# define GROUND_PATH "srcs/textures/GROUND.xpm"
# define CHAR_PATH "srcs/textures/CHAR.xpm"
# define COIN_PATH "srcs/textures/COIN.xpm"
# define EXIT_PATH "srcs/textures/EXIT.xpm"

# define WALL_INDEX 0
# define GROUND_INDEX 1
# define CHAR_INDEX 2
# define COIN_INDEX 3
# define EXIT_INDEX 4

typedef struct s_map
{
	void	*connection;
	void	*window;
	char	**data;
	void	*textures[5];
	int		height;
	int		width;
	bool	character;
	int		x;
	int		y;
	int		got_coin;
	int		moove;
	bool	exit;
	int		coin;
	int		img_size;
	
}	t_map;

int		main(int argc, char **argv);

//init
t_map	init_map(char	*argv);
void	init_value(t_map *map);
t_map	create_map(t_map map, int fd);
bool	init_mlx(t_map *map);

//check map
bool	check_map(t_map *map);
bool	check_oblong(char *line, int width);
bool	check_doubles(char *line, t_map *map);
bool	check_wall(t_map *map);
void	parsing(t_map *map, int y, int x, char **tab, int *coin, bool *exit);
void	check_path(t_map *map);

//inputs
int		close_window(t_map *map);
int		handle_inputs(int keysym, t_map *map);
void	moove_player(t_map *map, int x, int y);
bool	is_wall_exit(t_map *map, char *c);
void	end_game(t_map *map, int c);

//free
void	free_map(t_map *map);
void	free_mlx(t_map *map, bool type);
void	free_textures(t_map *map, int index);
void	free_tab(char **tab);

//utils
void	print_map(char **map);
void	find_player(t_map *map);

//display
void	*check_textures(t_map *map, char *path, int index);
void	select_texture(t_map *map, char texture, int width, int height);
void	init_textures(t_map *map);
void	display_map(t_map *map);

#endif
