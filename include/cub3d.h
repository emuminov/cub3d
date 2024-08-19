/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:16:25 by eandre            #+#    #+#             */
/*   Updated: 2024/08/20 00:56:20 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/libft/ft_printf/ft_printf.h"
# include "../src/libft/get_next_line/get_next_line.h"
# include "../src/libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# define TILE_SIZE 128
# define RADIAN_TO_DEGREE_SCALING 0.0174533

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
	char			*north_path;
	char			*east_path;
	char			*south_path;
	char			*west_path;
	int				map_fd;
	int				*floor_c;
	int				*ceiling_c;
	char			*map_1d;
	int				keys_finish;
}					t_config_parsing;

typedef struct s_dda_params
{
	t_grid_coordsf	ray_step;
	t_grid_coordsf	rate_of_change;
	t_grid_coordsf	dist_until_grid_side;
	t_grid_coordsi	inspected_grid;
	bool			found_wall;
	double			camera;
	double			distance;
	double			max_distance;
}					t_dda_params;

typedef struct s_player
{
	t_grid_coordsf	pos;
	t_grid_coordsf	collision_point;
	t_vectorf		dir;
	t_vectorf		plane;
}					t_player;

typedef struct s_config
{
	int				north_fd;
	int				east_fd;
	int				south_fd;
	int				west_fd;
	int				*floor_c;
	int				*ceiling_c;
}					t_config;

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
	char			**map;
	t_config		conf;
	t_controls		controls;
	t_grid_coordsi	map_size;
	t_grid_coordsf	minimap_camera;
	t_pixel_point	window_size;
	t_grid_coordsf	rays[30];
	int				old_mouse_pos;
}					t_game;

enum				e_direction
{
	up,
	down,
	left,
	right
};

/*					// PARSE \\								*/
int					parse_line(char *gnl, t_config_parsing *conf);
void				pre_parsing(int fd, t_config_parsing *conf);
/*					// INNIT \\								*/
t_config_parsing	config_parsing_init(void);
t_config			config_init(void);
t_game				game_init(int argc, char **argv);
/*					// KEY MANAGEMENT \\					*/
int					north_key_manager(char *gnl, t_config_parsing *conf);
int					east_key_manager(char *gnl, t_config_parsing *conf);
int					west_key_manager(char *gnl, t_config_parsing *conf);
int					south_key_manager(char *gnl, t_config_parsing *conf);
int					ceiling_key_manager(char *gnl, t_config_parsing *conf);
int					floor_key_manager(char *gnl, t_config_parsing *conf);
int					error_key(char *gnl, t_config_parsing *conf, int i,
						int strcmp_value);
int					key_finish_check(char *gnl, t_config_parsing *conf);
/*					// PATH MANAGEMENT \\					*/
void				paths_errors(t_config_parsing *conf);
void				path_format_checker(char *str, t_config_parsing *conf);
void				open_paths(t_config_parsing *conf_p, t_config *conf);
int					error_manager(int argc, char *argv);
void				open_error_manager(t_config_parsing *conf_p, t_config *conf,
						char *path, char *name);
/*					// UTILS \\								*/
unsigned char		ft_atoc(const char *str, char *gnl, t_config_parsing *conf);
int					charcmp(char *str, char c);
char				*ft_strjoin_free(char *s1, char *s2);
/*					// FREE \\								*/
void				free_config_p(t_config_parsing *conf);
void				free_config(t_config *conf);
void				free_tab(char **tab);

/*////////////////////MATH FUNCS\\\\\\\\\\\\\\\\\\\*/
/* Used for pure calculations with no side effects. Operate on ints, doubles and
 * vectors that represent direction, grid coordinates, pixels on window. */
/*                  // VECTORF \\ 							*/
double				vectorf_len(t_vectorf v);
t_vectorf			vectorf_norm(t_vectorf v);
t_vectorf			vectorf_sub(t_vectorf v1, t_vectorf v2);
t_vectorf			vectorf_add(t_vectorf v1, t_vectorf v2);
t_vectorf			vectorf_dir(t_vectorf start, t_vectorf end);
t_vectorf			vectorf_scale(t_vectorf v, double nbr);
t_vectorf			vectorf_abs(t_vectorf v);
t_vectorf			vectorf_rotate(t_vectorf dir, double theta);
t_vectorf			vectorf_round(t_vectorf v);
t_vectorf			vectorf_epsilon(t_vectorf dir);

/*					// GRID PIXEL CONVERSIONS \\ 			*/
t_pixel_point		grid_coordsf_to_pixel_point(t_grid_coordsf v);
t_pixel_point		grid_coordsi_to_pixel_point(t_grid_coordsi v);
t_grid_coordsf		pixel_point_to_grid_coordsf(t_pixel_point v);
t_grid_coordsi		pixel_point_to_grid_coordsi(t_pixel_point v);

/*					// GRID BOUNDS CHECKING \\ 				*/
bool				is_in_bounds_of_grid(t_grid_coordsi v,
						t_grid_coordsi map_size);
bool				is_beyond(t_grid_coordsf v1, t_grid_coordsf v2,
						t_vectorf dir);

/* 					// VECTORI \\ 							*/
t_vectori			vectori_sub(t_vectori v1, t_vectori v2);
t_vectori			vectori_add(t_vectori v1, t_vectori v2);

/*					// UTILS \\  							*/
double				abs_f(double n);
double				sign_f(double nbr);
int					max(int n1, int n2);

/*////////////////////GAME LOOP\\\\\\\\\\\\\\\\\\\*/
/* Functions for handling graphics and controls, operations on game struct,
 * matrix that represent the game map, wrappers for easier use of
 * the mlx library. */
/*					// CONTROLS HANDLING \\ 				*/
bool				is_any_key_pressed(t_game *g);
int					handle_key_press(int keysym, t_game *g);
int					handle_key_release(int keysym, t_game *g);
t_vectorf			mouse_pos_to_grid_coordsf(t_game *g);

/*					// DRAW UTILS \\ 						*/
/* Functions for drawing simple shapes. */
void				draw_line(t_img *frame, t_pixel_point start,
						t_pixel_point end, int color);
void				draw_grid(t_game *g, t_img *frame);
void				draw_hollow_square(t_img *frame, t_pixel_point pos,
						int size, int color);
void				draw_square(t_img *frame, t_pixel_point pos, int size,
						int color);
void				draw_tile(t_img *frame, t_grid_coordsi p, int color);

/*					// INIT GAME \\ 						*/
/* Initializes mlx, creates new window, initializes game struct */
int					init_game(t_game *g, int x, int y);

/*					// MINIMAP \\							*/
/* TODO: under construction */
void				draw_minimap(t_game *g);

/*					// MLX IMG UTILS \\						*/
unsigned int		get_pixel_of_img(t_img img, t_pixel_point p);
void				put_pixel_on_img(t_img *img, t_pixel_point p, int color);
int					init_img_data(void *mlx, t_img *img, t_pixel_point p);

/*					// MOVEMENT \\								*/
t_grid_coordsf		move_player(t_player p, const t_controls *controls);
t_vectorf			get_movement_dir(const t_controls *controls,
						const t_player *player);
void				resolve_rotation(t_game *g);
void				resolve_movement(t_game *g);

/*					// ULDATE GAME STATE \\					*/
/* Everything that updates the state during runtime. For now it's a simple
 * function that includes resolution of movement and rotations. */
void				update_game_state(t_game *g);

/*					// DDA \\								*/
/* Important algorithm for finding walls and collision points. */
t_vectorf			check_wall_in_dir(t_game *g, t_dda_params *dp,
						t_grid_coordsf start, t_vectorf dir,
						double max_distance);

/*					// MOUSE \\								*/
/* Handles rotations with mouse. */
void handle_mouse(t_game *g);

/*					// TESTING 2D PLANE LOOP \\				*/
/* Loop for purely testing purposes. Renders topdown 2d plane view with
 * wall ray and collision rays. */
int					init_testing_2d_plane_loop(void);

#endif
