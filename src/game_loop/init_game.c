/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:05:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/20 00:47:42 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"

/* Contains functions that contain functions for initialization of graphics */

// TODO: replace hardcoded values with the result from parsing
// TODO: check for malloc errors
int	init_game(t_game *g, int x, int y)
{
	int	mouse_pos_y;

	(void)mouse_pos_y;
	g->window_size.x = x;
	g->window_size.y = y;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, x, y, "Cub3d");
	init_img_data(g->mlx, &g->frame, g->window_size);
	g->player.pos = (t_vectorf){.x = 5.2, .y = 3.5};
	g->player.dir = (t_vectorf){.x = 1, .y = 0};
	g->map_size = (t_grid_coordsi){.x = 10, .y = 10}; // size of actual map
	mlx_mouse_get_pos(g->mlx, g->win, &g->old_mouse_pos, &y);
	return (0);
}
