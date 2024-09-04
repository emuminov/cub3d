/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:16:25 by eandre            #+#    #+#             */
/*   Updated: 2024/09/04 22:06:20 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "constants.h"
# include "textures_paths.h"
# include <linux/limits.h>
# include <stdbool.h>

typedef enum e_etiles
{
	empty = ' ',
	floor_tile = '0',
	wall = '1',
	door_closed = 'D',
	door_opened = 'O',
	player_north = 'N',
	player_south = 'S',
	player_east = 'E',
	player_west = 'W',
}					t_tiles;

typedef enum e_texture_dir
{
	north_tex,
	south_tex,
	east_tex,
	west_tex,
}					t_texture_dir;

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

typedef struct s_dda_params
{
	t_grid_coordsf	ray_step;
	t_grid_coordsf	rate_of_change;
	t_grid_coordsf	dist_until_grid_side;
	t_grid_coordsf	last_cell;
	t_grid_coordsi	inspected_grid;
	bool			is_cell_found;
	int				side;
	double			camera;
	double			distance;
	double			max_distance;
	t_tiles			type_of_found_cell;
}					t_dda_params;

typedef struct s_player
{
	t_grid_coordsf	pos;
	t_vectorf		dir;
	t_vectorf		plane;
	bool			has_flower;
	bool			takes_flower;
}					t_player;

typedef struct s_config
{
	char			paths[4][PATH_MAX];
	int				floor_c;
	int				ceil_c;
	t_grid_coordsi	map_size;
}					t_config;

typedef struct s_controls
{
	bool			rotate_left_pressed;
	bool			rotate_right_pressed;
	bool			move_up_pressed;
	bool			move_down_pressed;
	bool			move_left_pressed;
	bool			move_right_pressed;
	bool			punch_key_pressed;
}					t_controls;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			frame;
	t_img			wall_textures[4];
	t_img			idle_textures[IDLE_FRAMES];
	t_img			walk_textures[WALK_FRAMES];
	t_img			idle_flower_textures[IDLE_FLOWER_FRAMES];
	t_img			walk_flower_textures[WALK_FLOWER_FRAMES];
	t_img			flower_out_textures[FLOWER_OUT_FRAMES];
	t_img			flower_in_textures[FLOWER_IN_FRAMES];
	t_img			door_texture;
	t_player		player;
	int				*len_tab;
	t_dda_params	dp;
	char			**map;
	t_config		conf;
	t_controls		controls;
	t_pixel_point	window_size;
	int				mouse_pos;
	bool			mouse_enabled;
	t_pixel_point	old_mouse_pos;
	t_grid_coordsf	rays[WINDOW_WIDTH];
}					t_game;

// PARSING
int					extract_params_from_cub_file(t_game *g, int argc,
						char **argv);

// GRAPHICS
void				render_3d_graphics(t_game *g);

// GAME_LOGIC
bool				check_cell_in_dir(t_game *g, t_vectorf dir,
						double max_distance, char *checked_tiles);
void				start_game_loop(t_game *g);
int					create_window(t_game *g);
int					init_animation_textures(t_game *g);
int					init_wall_textures(t_game *g);
int					center_mouse_in_window(int x, int y, t_game *g);

// INIT
int					start_game(int argc, char **argv);

// FREE
void				free_tab(char **tab);
void				free_game(t_game *g);
void				destroy_textures_array(t_game *g, t_img *textures,
						int size);
void				destroy_textures_array(t_game *g, t_img *textures,
						int size);

#endif
