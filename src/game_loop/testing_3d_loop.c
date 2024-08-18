/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_3d_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:42:10 by eandre            #+#    #+#             */
/*   Updated: 2024/08/18 20:53:00 by eandre           ###   ########.fr       */
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
	t_grid_coordsf	ray;
	double			perp_wall_dist;
	int				draw_end;
	int				draw_start;
	int				line_height;

	// draw_grid(g, &g->frame);
	// draw_square(&g->frame, grid_coordsf_to_pixel_point(g->player.pos), 25,
	// 	0xAA00AA);

	ray = check_wall_in_dir(g, &g->dp, g->player.pos, g->player.dir, 100);
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
	}
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

// int	init_img2_data(void *mlx, t_img2 *img, t_pixel_point p)
// {
// 	img->dimensions = p;
// 	img->img = mlx_new_image(mlx, p.x, p.y);
// 	if (!img->img)
// 		return (-1);
// 	img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
// 			&img->line_len, &img->endian);
// 	return (0);
// }

int	init_testing_3d_loop(void)
{
	static t_game	g;
	int				size;

	init_game(&g, 640, 640);
	create_basic_map(&g);
	g.frame.img = mlx_xpm_file_to_image(g.mlx, "Stephane.xpm", &size, &size);
	g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bits_per_pixel, &g.frame.line_len, &g.frame.endian);
	// void	*temporary;
	// int		i = 0;
	// int		*address;
	// int		y = 0;
	// int		x = 0;
	// init_img2_data(g.mlx, &g.img[0], g.window_size);
	// init_img2_data(g.mlx, &g.img[1], g.window_size);
	// init_img2_data(g.mlx, &g.img[2], g.window_size);
	// init_img2_data(g.mlx, &g.img[3], g.window_size);
	// g.xpm[0] = ft_strdup("Stephane.xpm");
	// g.xpm[1] = ft_strdup("Stephane.xpm");
	// g.xpm[2] = ft_strdup("Stephane.xpm");
	// g.xpm[3] = ft_strdup("Stephane.xpm");
	// g.xpm[4] = NULL;
	// while (i < 4)
	// {
	// 	temporary = mlx_xpm_file_to_image(g.mlx, g.xpm[i],
	// 		&(g.img[i].dimensions.x), &(g.img[i].dimensions.y));
	// 	g.img[i].img = temporary;
	// 	if (!g.img[i].img)
	// 		return (1);
	// 	address = (int *)mlx_get_data_addr(g.img[i].img,
	// 		&g.img[i].bits_per_pixel, &g.img[i].line_len,
	// 		&g.img[i].endian);
	// 	g.img[i].addr = address;
	// 	if (!g.img[i].addr)
	// 		return (1);
	// 	while (y < g.img[i].dimensions.y)
	// 	{
	// 		x = 0;
	// 		while (x < g.img[i].dimensions.x)
	// 		{
	// 			g.texture[i][g.img[i].dimensions.y * y + x] =
	// 				(g.img[i].addr[g.img[i].dimensions.y * y + x]);
	// 			x++;
	// 		}
	// 		y++;
	// 	}
	// 	mlx_destroy_image(g.mlx, g.img[i].img);
	// 	i++;
	// }
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
