/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:16:25 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 02:43:52 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../src/libft/get_next_line/get_next_line.h"
// # include "../src/libft/libft.h"
# include <stdbool.h>

typedef enum	e_etiles
{
	empty = '0',
	wall = '1',
	door_closed = 'D',
	door_opened = 'O',
	player_north = 'N',
	player_south = 'S',
	player_east = 'E',
	player_west = 'W',
}				t_tiles;

typedef struct s_vectorf
{
	double			x;
	double			y;
}					t_vectorf;

typedef struct s_vectori
{
	int				x;
	int				y;
}					t_vectori;

typedef t_vectorf	t_grid_coordsf;
typedef t_vectori	t_pixel_point;
typedef t_vectori	t_grid_coordsi;

/* All the relevant data to rendered images */
typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
	t_vectori		dimensions;
}					t_img;

typedef struct s_config_parsing
{
	char	*north_path;
	char	*east_path;
	char	*south_path;
	char	*west_path;
	int		map_fd;
	int		floor_c[3];
	int		ceiling_c[3];
	char	*map_1d;
	int		keys_finish;
}	t_config_parsing;

typedef struct s_dda_params
{
	t_grid_coordsf	ray_step;
	t_grid_coordsf	rate_of_change;
	t_grid_coordsf	dist_until_grid_side;
	t_grid_coordsi	inspected_grid;
	bool			found_cell;
	int				side;
	double			camera;
	double			distance;
	double			max_distance;
	t_tiles			type_of_found_cell;
}					t_dda_params;

typedef struct	s_player
{
	t_grid_coordsf	pos;
	t_grid_coordsf	size;
	t_vectorf		dir;
	t_vectorf		plane;
}					t_player;

typedef struct s_config
{
	int		north_fd;
	int		east_fd;
	int		south_fd;
	int		west_fd;
	int		floor_c;
	int		ceiling_c;
}	t_config;


typedef struct s_controls
{
	bool			rotate_left_pressed;
	bool			rotate_right_pressed;
	bool			move_up_pressed;
	bool			move_down_pressed;
	bool			move_left_pressed;
	bool			move_right_pressed;
}					t_controls;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			frame;
	t_player		player;
	t_dda_params	dp;
	char			*xpm[5];
	char			**map;
	char			**map_dup;
	t_config		conf;
	t_controls		controls;
	t_grid_coordsi	map_size;
	t_pixel_point	minimap_size;
	t_pixel_point	window_size;
	t_grid_coordsf	rays[30];
	int				old_mouse_pos;
	t_img			texture;
}					t_game;

// PARSING
int					parse_cub_map(t_game *g, int argc, char **argv);

// GRAPHICS
void				render_3d_graphics(t_game *g);

// GAME_LOGIC
int					init_game(t_game *g, int x, int y);
t_vectorf			check_cell_in_dir(t_game *g, t_grid_coordsf start,
		t_vectorf dir, double max_distance, char *checked_tiles);

// INIT
int					init_game_loop(int argc, char **argv);

// FREE
void				free_config_p(t_config_parsing *conf);
void				free_config(t_config *conf);
void				free_tab(char **tab);
#endif
