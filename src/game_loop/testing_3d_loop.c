/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_3d_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:42:10 by eandre            #+#    #+#             */
/*   Updated: 2024/08/21 17:46:46 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#include <math.h>

static void	create_basic_map(t_game *g);
void		mlx_place_pixel(int x, int y, int colour, t_game *g);

static void	render_3d_graphics(t_game *g)
{
	// t_grid_coordsf	ray;
	// double			perp_wall_dist;
	int				draw_end;
	int				draw_start;
	int				line_height;
	int				x;
	int				y;

	// draw_grid(g, &g->frame);
	// draw_square(&g->frame, grid_coordsf_to_pixel_point(g->player.pos), 25,
	// 	0xAA00AA);

// out loop goes from -33 to 33
// we rotate the player direction to the current degree in the iteration
// we cast rays
// we draw things depending on what how far away the walls are
// the distance is: 
// 

// yx -------------------------
// |
// |
// |
// |
// |
// |

	// if (ray.x != -1)
	// {
	x = 0;
	while (x < g->window_size.x)
	{
		check_wall_in_dir(g, &g->dp, g->player.pos, g->player.dir, 100);
		// if (g->dp.side == 0)
		// 	perp_wall_dist = (g->dp.inspected_grid.x - g->dp.ray_step.x);
		// else
		// 	perp_wall_dist = (g->dp.inspected_grid.y - g->dp.ray_step.y);
		line_height = (int)(g->window_size.y / g->dp.distance);
		draw_start = -line_height / 2 + g->window_size.y / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + g->window_size.y / 2;
		if (draw_end >= g->window_size.y)
			draw_end = g->window_size.y - 1;
		y = draw_start;
		while (y < draw_end)
		{
			put_pixel_on_img(&g->frame, (t_pixel_point){x,y}, get_pixel_of_img(g->frame, (t_pixel_point){x, y}));
			// put_pixel_on_img(&g->frame, (t_pixel_point){x,y}, get_pixel_of_img(g->frame, (t_pixel_point){x, y}));
			y++;
		}
		x++;
	}
	// }
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

static int	testing_3d_loop(t_game *g)
{
	update_game_state(g);
	render_3d_graphics(g);
	return (0);
}

// void	mlx_place_pixel(int x, int y, int colour, t_game *g)
// {
// 	char	*distance;

// 	distance = g->frame.addr + 
// 		(y * g->frame.line_len + x * (g->frame.bits_per_pixel / 8));
// 	*(unsigned int *)distance = colour;
// }


int	init_testing_3d_loop(void)
{
	static t_game	g;
	int				size;

	init_game(&g, 640, 640);
	create_basic_map(&g);
	g.frame.img = mlx_xpm_file_to_image(g.mlx, "Stephane.xpm", &size, &size);
	g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bits_per_pixel, &g.frame.line_len, &g.frame.endian);
	// mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);
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
