/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:05:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/17 01:07:24 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"

/* Contains functions that contain functions for initialization of graphics */

// TODO: replace hardcoded values with the result from parsing
// TODO: check for malloc errors
int	init_game(t_game *g, int x, int y)
{
	g->window_size.x = x;
	g->window_size.y = y;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, x, y, "Cub3d");
	init_img_data(g->mlx, &g->frame, g->window_size);
	g->player.pos = (t_vectorf){.x = 1.5, .y = 1.5};
	g->player.dir = (t_vectorf){.x = 1, .y = 0};
	g->player.dir = vectorf_rotate(g->player.dir, -225);
	g->map_size = (t_grid_coordsi){.x = 10, .y = 10}; // size of actual map
	return (0);
}
