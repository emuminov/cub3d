/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_2d_plane_loop.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:19:45 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/15 20:05:01 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"

// static void	render_2d_plane_graphic(t_game *g);
static int	testing_2d_plane_loop(t_game *g);
static void	create_basic_map(t_game *g);

static void	render_minimap_graphic(t_game *g)
{
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

/* Draws a simple 2d plane for testing purposes
 * TODO: check for possible memory failures */
int	init_testing_2d_plane_loop(void)
{
	static t_game	g;

	init_game(&g, 640, 640);
	create_basic_map(&g);
	mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);
	mlx_hook(g.win, 2, (1L << 0), handle_key_press, &g);
	mlx_hook(g.win, 3, (1L << 1), handle_key_release, &g);
	mlx_loop_hook(g.mlx, testing_2d_plane_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}

// static void	render_2d_plane_graphic(t_game *g)
// {
// 	t_grid_coordsf	ray;
//
// 	ray = check_wall_in_dir(g, &g->dp, g->player.pos, g->player.dir, 100);
// 	draw_grid(g, &g->frame);
// 	draw_square(&g->frame, grid_coordsf_to_pixel_point(g->player.pos), 25,
// 		0xAA00AA);
// 	if (ray.x != -1)
// 	{
// 		draw_line(&g->frame, grid_coordsf_to_pixel_point(g->player.pos),
// 			grid_coordsf_to_pixel_point(ray), 0xAA00AA);
// 		draw_hollow_square(&g->frame, grid_coordsf_to_pixel_point(ray), 25,
// 			0x2AAA2A);
// 	}
// 	if (g->player.collision_point.x != -1)
// 	{
// 		draw_line(&g->frame, grid_coordsf_to_pixel_point(g->player.pos),
// 			grid_coordsf_to_pixel_point(g->player.collision_point), 0xAA1A1A);
// 		draw_hollow_square(&g->frame,
// 			grid_coordsf_to_pixel_point(g->player.collision_point), 25,
// 			0xAA1A1A);
// 	}
// 	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
// }

/* Update and render loop for testing 2d plane */
static int	testing_2d_plane_loop(t_game *g)
{
	update_game_state(g);
	// render_2d_plane_graphic(g);
	render_minimap_graphic(g);
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
	g->map[3][5] = '2';
	g->map[3][2] = '1';
	g->map[1][2] = '1';
}
