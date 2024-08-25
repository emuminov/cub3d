/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:05:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 17:38:36 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/game_logic.h"
#include "../minilibx-linux/mlx.h"
#include <X11/XKBlib.h>

/* Contains functions that contain functions for initialization of graphics */

static int	game_loop(t_game *g)
{
	update_game_state(g);
	render_3d_graphics(g);
	return (0);
}

static void	start_mlx_loop(t_game *g)
{
	mlx_hook(g->win, 2, (1L << 0), handle_key_press, g);
	mlx_hook(g->win, 3, (1L << 1), handle_key_release, g);
	mlx_hook(g->win, DestroyNotify, StructureNotifyMask,
			exit_hook_cross, g);
	mlx_loop_hook(g->mlx, game_loop, g);
	mlx_loop(g->mlx);
}

static void	init_textures(t_game *g)
{
	g->texture[north_tex].img = mlx_xpm_file_to_image(g->mlx, g->conf.
	, &g->texture[north_tex].dimensions.x, &g->texture[north_tex].dimensions.y);
	if (g->texture[north_tex].dimensions.x > g->window_size.x 
	|| g->texture[north_tex].dimensions.y > g->window_size.y)
		resize_image(g, &g->texture[north_tex]
		, g->window_size.x, g->window_size.y);
	g->texture[north_tex].addr = mlx_get_data_addr(g->texture[north_tex].img, &g->texture[north_tex].bits_per_pixel, &g->texture[north_tex].line_len, &g->texture[north_tex].endian);
	g->texture[south_tex].img = mlx_xpm_file_to_image(g->mlx, "tile1.xpm", &g->texture[south_tex].dimensions.x, &g->texture[south_tex].dimensions.y);
	if (g->texture[south_tex].dimensions.x > g->window_size.x || g->texture[south_tex].dimensions.y > g->window_size.y)
		resize_image(g, &g->texture[south_tex], g->window_size.x, g->window_size.y);
	g->texture[south_tex].addr = mlx_get_data_addr(g->texture[south_tex].img, &g->texture[south_tex].bits_per_pixel, &g->texture[south_tex].line_len, &g->texture[south_tex].endian);
	g->texture[west_tex].img = mlx_xpm_file_to_image(g->mlx, "tile1.xpm", &g->texture[west_tex].dimensions.x, &g->texture[west_tex].dimensions.y);
	if (g->texture[west_tex].dimensions.x > g->window_size.x || g->texture[west_tex].dimensions.y > g->window_size.y)
		resize_image(g, &g->texture[west_tex], g->window_size.x, g->window_size.y);
	g->texture[west_tex].addr = mlx_get_data_addr(g->texture[west_tex].img, &g->texture[west_tex].bits_per_pixel, &g->texture[west_tex].line_len, &g->texture[west_tex].endian);
	g->texture[east_tex].img = mlx_xpm_file_to_image(g->mlx, "tile1.xpm", &g->texture[east_tex].dimensions.x, &g->texture[east_tex].dimensions.y);
	if (g->texture[east_tex].dimensions.x > g->window_size.x || g->texture[east_tex].dimensions.y > g->window_size.y)
		resize_image(g, &g->texture[east_tex], g->window_size.x, g->window_size.y);
	g->texture[east_tex].addr = mlx_get_data_addr(g->texture[east_tex].img, &g->texture[east_tex].bits_per_pixel, &g->texture[east_tex].line_len, &g->texture[east_tex].endian);
}

/* Allocates new image and initializes parameters of its struct */
// TODO: replace hardcoded values with the result from parsing
// TODO: check for malloc errors
int	init_game(t_game *g, int x, int y)
{
	int	dummy_mouse_pos_y;

	(void)dummy_mouse_pos_y;
	g->window_size.x = x;
	g->window_size.y = y;
	g->player.pos = (t_grid_coordsf){.x = 1.5, .y = 1.5};
	g->player.size = (t_grid_coordsf){.x = 0.1, .y = 0.1};
	g->player.dir = (t_vectorf){.x = 1, .y = 0};
	g->player.plane = (t_vectorf){.x = 0, .y = 0.66};
	g->minimap_size = (t_pixel_point){.x = 160, .y = 160};
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, x, y, "Cub3d");
	init_textures(g);
	
	init_img_data(g->mlx, &g->frame, g->window_size);
	mlx_mouse_get_pos(g->mlx, g->win, &g->old_mouse_pos, &y);
	start_mlx_loop(g);
	return (0);
}
