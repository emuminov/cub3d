/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_3d_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:42:10 by eandre            #+#    #+#             */
/*   Updated: 2024/08/15 21:48:51 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <X11/XKBlib.h>
#include <X11/Xutil.h>

static void	create_basic_map(t_game *g);

static void	render_3d_graphics(t_game *g)
{
	t_grid_coordsf	ray;
	double			perp_wall_dist;
	int				draw_end;
	int				draw_start;
	int				line_height;

	draw_grid(g, &g->frame);
	// draw_square(&g->frame, grid_coordsf_to_pixel_point(g->player.pos), 25,
	// 	0xAA00AA);
	ray = check_wall_in_dir(g, &g->dp, g->player.pos, g->player.dir, 100);
	//calculate lowest and highest pixel to fill in current stripe
	if (ray.x != -1)
	{
		if (g->dp.side == 0)
			perp_wall_dist = (g->dp.inspected_grid.x - g->dp.ray_step.x);
		else
			perp_wall_dist = (g->dp.inspected_grid.y - g->dp.ray_step.y);
		line_height = (int)(g->window_size.y / perp_wall_dist);
		draw_start = -line_height / 2 + g->window_size.y / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + g->window_size.y / 2;
		if (draw_end >= g->window_size.y)
			draw_end = g->window_size.y - 1;
		draw_line(&g->frame, grid_coordsf_to_pixel_point(g->player.pos),
			grid_coordsf_to_pixel_point(ray), 0xAA00AA);
		draw_hollow_square(&g->frame, grid_coordsf_to_pixel_point(ray), 25,
			0x2AAA2A);
		g->player.plane = vectorf_add(g->player.pos,
				vectorf_scale(vectorf_rotate(g->player.dir, 90), -1));
		draw_line(&g->frame, grid_coordsf_to_pixel_point(g->player.pos),
			grid_coordsf_to_pixel_point(g->player.plane), 0xAA00AA);
	}
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

static int	testing_3d_loop(t_game *g)
{
	update_game_state(g);
	render_3d_graphics(g);
	return (0);
}

int	init_testing_3d_loop(void)
{
	static t_game	g;

	init_game(&g, 640, 640);
	create_basic_map(&g);
	mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);
	mlx_hook(g.win, 2, (1L << 0), handle_key_press, &g);
	mlx_hook(g.win, 3, (1L << 1), handle_key_release, &g);
	mlx_hook(g.win, DestroyNotify, StructureNotifyMask,
		exit_hook_cross, &g);
	mlx_loop_hook(g.mlx, testing_3d_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}

static void	create_basic_map(t_game *g)
{
	int	x;
	int	y;

	g->map = ft_calloc(10, sizeof(char *));
	y = 0;
	while (y < 10)
	{
		g->map[y] = ft_calloc(10, sizeof(char));
		x = 0;
		while (x < 10)
		{
			if (x == 0 || x == 9 || y == 0 || y == 9)
				g->map[y][x] = '1';
			else
				g->map[y][x] = '0';
			x++;
		}
		y++;
	}
	g->map[2][2] = '2';
}
