/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:05:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 19:01:27 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_logic.h"
#include "../../include/constants.h"
#include "../minilibx-linux/mlx.h"
#include "../../include/cub3d.h"
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

int	init_wall_textures(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (init_texture(g, &g->wall_textures[i], g->conf.paths[i]) == 1)
			return (1);
	}
	return (0);
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
