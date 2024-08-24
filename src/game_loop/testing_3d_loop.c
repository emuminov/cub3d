/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_3d_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:42:10 by eandre            #+#    #+#             */
/*   Updated: 2024/08/23 21:20:15 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#include <math.h>

// static void	create_basic_map(t_game *g);
void		mlx_place_pixel(int x, int y, int colour, t_game *g);

static void	render_3d_graphics(t_game *g)
{
	int				draw_end;
	int				draw_start;
	int				line_height;
	int				x;
	int				y;
	double			cam_x;
	t_grid_coordsf	ray;
	t_vectorf		ray_dir;

// yx -------------------------
// |
// |
// |
// |
// |
// |
	draw_ceiling_and_floor(g);
	x = 0;
	while (x < g->window_size.x)
	{
		cam_x = 2 * x / (double)g->window_size.x - 1;
		ray_dir = vectorf_add(g->player.dir, vectorf_scale(g->player.plane, cam_x));
		ray = check_cell_in_dir(g, g->player.pos, ray_dir, 100, "1D");
		if (ray.x != -1)
		{
			// printf("rate of change: %f %f\n", g->dp.rate_of_change.x, g->dp.rate_of_change.y);
			double wallX; //where exactly the wall was hit
			line_height = (int)(g->window_size.y / g->dp.distance);
			draw_start = -(line_height) / 2 + g->window_size.y / 2;
			if (draw_start < 0)
				draw_start = 0;
			draw_end = line_height / 2 + g->window_size.y / 2;
			if (draw_end >= g->window_size.y)
				draw_end = g->window_size.y - 1;
			if (g->dp.side == 0)
				wallX = g->player.pos.y + g->dp.distance * ray_dir.y;
			else
				wallX = g->player.pos.x + g->dp.distance * ray_dir.x;
			wallX -= floor(wallX);
			int texX = (int)(wallX * (double)g->texture.dimensions.x);
			if((g->dp.side == 0 && ray_dir.x > 0) 
			|| (g->dp.side == 1 && ray_dir.y < 0))
				texX = g->texture.dimensions.x - texX - 1;
			
			double step = 1.0 * g->texture.dimensions.y / line_height;
			double texPos = (draw_start - (double)g->window_size.y / 2 + (double)line_height / 2) * step;
			y = draw_start;
			while (y < draw_end)
			{
				int texY = (int)texPos & (g->texture.dimensions.y - 1);
				texPos += step;
				
				// int	color = get_pixel_of_img(g->frame, (t_pixel_point){texX, texY});
				// if(g->dp.side == 1) color = (color >> 1) & 8355711; //
				put_pixel_on_img(&g->frame, (t_pixel_point){x,y}, get_pixel_of_img(g->texture, (t_pixel_point){texX, texY}));
				y++;
			}
		}
		x++;
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

int	init_testing_3d_loop(int argc, char **argv)
{
	static t_game	g;
	int					fd;
	t_config_parsing	conf_p;

	init_game(&g, 640, 640);

	fd = error_manager(argc, argv[1]);
	conf_p = config_parsing_init();
	g.conf = config_init();
	pre_parsing(fd, &conf_p);
	paths_errors(&conf_p, &g.conf);
	g.map = ft_split(conf_p.map_1d, '\n');
	g.conf.ceiling_c = conf_p.ceiling_c;
	g.conf.floor_c = conf_p.floor_c;
	// parse_map(g.map);
	int	i = 0;
	int	j = 0;
	while (g.map[i])
	{
		if ((int)ft_strlen(g.map[i]) > j)
			j = (int)ft_strlen(g.map[i]);
		i++;
	}
	g.map_size = (t_grid_coordsi){.x = j, .y = i};
	g.texture.img = mlx_xpm_file_to_image(g.mlx, "tile1.xpm", &g.texture.dimensions.x, &g.texture.dimensions.y);
	g.texture.addr = mlx_get_data_addr(g.texture.img, &g.texture.bits_per_pixel, &g.texture.line_len, &g.texture.endian);
	printf("%p\n", g.conf.floor_c);
	printf("%p\n", g.conf.ceiling_c);
	mlx_hook(g.win, 2, (1L << 0), handle_key_press, &g);
	mlx_hook(g.win, 3, (1L << 1), handle_key_release, &g);
	mlx_hook(g.win, DestroyNotify, StructureNotifyMask,
		exit_hook_cross, &g);
	mlx_loop_hook(g.mlx, testing_3d_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}

// static void	create_basic_map(t_game *g)
// {
// 	int	x;
// 	int	y;

// 	g->map = ft_calloc(10, sizeof(char *));
// 	y = 0;
// 	while (y < 10)
// 	{
// 		g->map[y] = ft_calloc(10, sizeof(char));
// 		x = 0;
// 		while (x < 10)
// 		{
// 			if (x == 0 || x == 9 || y == 0 || y == 9)
// 				g->map[y][x] = '1';
// 			else
// 				g->map[y][x] = '0';
// 			x++;
// 		}
// 		y++;
// 	}
// 	g->map[2][2] = '2';
// 	g->map[2][1] = '1';
// 	g->map[2][3] = '1';
// 	g->map[2][4] = '1';
// 	g->map[3][5] = '1';
// }
