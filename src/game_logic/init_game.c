/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:05:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 16:24:36 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_logic.h"
#include "../../include/constants.h"
#include "../minilibx-linux/mlx.h"
#include "../../include/cub3d.h"
#include "../libft/libft.h"
#include <X11/XKBlib.h>
#include <stdlib.h>
#include <stdio.h>

/* Contains functions that contain functions for initialization of graphics */

static int	game_loop(t_game *g);

int	create_window(t_game *g)
{
	if (init_img_data(g->mlx, &g->frame, g->window_size) == 1)
		return (1);
	g->win = mlx_new_window(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	if (g->win == NULL)
		return (1);
	return (0);
}

void	start_game_loop(t_game *g)
{
	mlx_mouse_get_pos(g->mlx, g->win, &g->old_mouse_pos.x, &g->old_mouse_pos.y);
	mlx_hook(g->win, 2, (1L << 0), handle_key_press, g);
	mlx_hook(g->win, 3, (1L << 1), handle_key_release, g);
	mlx_hook(g->win, 6, (1L << 6), handle_mouse, g);
	mlx_hook(g->win, DestroyNotify, StructureNotifyMask, exit_game, g);
	mlx_loop_hook(g->mlx, game_loop, g);
	mlx_loop(g->mlx);
}

void	init_wall_textures(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		g->wall_textures[i].img = mlx_xpm_file_to_image(g->mlx, g->conf.paths[i],
				&g->wall_textures[i].dimensions.x, &g->wall_textures[i].dimensions.y);
		if (g->wall_textures[i].img == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(g->mlx, g->wall_textures[i].img);
			mlx_destroy_display(g->mlx);
			free(g->mlx);
			free_tab(g->map);
			free(g->len_tab);
			printf("\033[0;31m""Error\nA xpm file is not valid!\n""\033[0m");
			exit(1);
		}
		if (g->wall_textures[i].dimensions.x > g->window_size.x
			|| g->wall_textures[i].dimensions.y > g->window_size.y)
			resize_image(g, &g->wall_textures[i], g->window_size.x, g->window_size.y);
		g->wall_textures[i].addr = mlx_get_data_addr(g->wall_textures[i].img,
				&g->wall_textures[i].bits_per_pixel, &g->wall_textures[i].line_len,
				&g->wall_textures[i].endian);
	}
}

static int	game_loop(t_game *g)
{
	if (is_move_key_pressed(g))
	{
		resolve_rotation(g);
		resolve_movement(g);
	}
	render_3d_graphics(g);
	return (0);
}
