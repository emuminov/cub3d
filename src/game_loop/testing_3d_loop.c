/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_3d_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:42:10 by eandre            #+#    #+#             */
/*   Updated: 2024/08/22 18:45:13 by eandre           ###   ########.fr       */
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
	int				draw_end;
	int				draw_start;
	int				line_height;
	double			wall_x;
	int				x;
	int				y;
	// double			texX;
	t_grid_coordsf	ray;
	t_img			tests;

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
	tests.dimensions.x = g->window_size.x;
	tests.dimensions.y = g->window_size.y;
	tests.img = mlx_new_image(g->mlx, tests.dimensions.x, tests.dimensions.y);
	tests.addr = mlx_get_data_addr(tests.img, &tests.bits_per_pixel, &tests.line_len, &tests.endian);
	x = 0;
	t_vectorf	test2;
	test2 = vectorf_rotate(g->player.dir, -33);
	while (x < g->window_size.x)
	{
		test2 = vectorf_rotate(test2, +0.5);
		ray = check_cell_in_dir(g, g->player.pos, test2, 100, "1D");
		if (ray.x != -1)
		{
			if (g->dp.side == 0)
				wall_x = g->player.pos.y + g->dp.distance * g->dp.inspected_grid.y;
			else
				wall_x = g->player.pos.x + g->dp.distance * g->dp.inspected_grid.x;
			wall_x -= floor(wall_x);
			// texX =(int)(wall_x * (double)g->frame.dimensions.x);
			// if (g->dp.side == 0 && g->dp.inspected_grid.x > 0)
			// 	texX = g->frame.dimensions.x - texX - 1;
			// if (g->dp.side == 1 && g->dp.inspected_grid.y < 0)
			// 	texX = g->frame.dimensions.x - texX - 1;
			line_height = (int)(g->window_size.y / g->dp.distance);
			
			draw_start = -line_height / 2 + g->window_size.y / 2;
			if (draw_start < 0)
				draw_start = 0;
			draw_end = line_height / 2 + g->window_size.y / 2;
			if (draw_end >= g->window_size.y)
				draw_end = g->window_size.y - 1;
			
			y = draw_start;
			// double step = 1.0 * g->frame.dimensions.y / line_height;
			// double texPos = (draw_start - g->window_size.y / 2 + line_height / 2) * step;
			while (y < draw_end)
			{
				// int texY = (int)texPos & (g->frame.dimensions.y - 1);
				// texPos += step;
				//get_pixel_of_img(g->frame, (t_pixel_point){texX, texY})
				int	color = 65280;
				if(g->dp.side == 1) color = (color >> 1) & 8355711;
				put_pixel_on_img(&tests, (t_pixel_point){x,y}, color);
				y++;
			}
		}
		x++;
	}
	// }
	mlx_put_image_to_window(g->mlx, g->win, tests.img, 0, 0);
	mlx_destroy_image(g->mlx, tests.img);
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
