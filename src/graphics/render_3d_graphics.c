/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:42:10 by eandre            #+#    #+#             */
/*   Updated: 2024/08/27 19:39:23 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/graphics.h"
#include "../../include/math_funcs.h"
#include "../minilibx-linux/mlx.h"
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#include <math.h>

void	render_3d_graphics(t_game *g)
{
	int				draw_end;
	int				draw_start;
	int				line_height;
	int				x;
	int				y;
	double			cam_x;
	t_grid_coordsf	ray;
	t_vectorf		ray_dir;
	int				texture_dir;
			double wallX;
	int				texX;
	double			step;
	double			texPos;
	int				texY;

	draw_ceiling_and_floor(&g->frame, g->conf.ceil_c, g->conf.floor_c);
	x = 0;
	while (x < g->window_size.x)
	{
		cam_x = 2 * x / (double)g->window_size.x - 1;
		ray_dir = vectorf_add(g->player.dir, vectorf_scale(g->player.plane,
					cam_x));
		ray = check_cell_in_dir(g, ray_dir, 100, "1D");
		if (ray.x != -1)
		{
			if (g->dp.side == 0)
			{
				if (ray_dir.x < 0)
					texture_dir = west_tex;
				else
					texture_dir = east_tex;
			}
			else
			{
				if (ray_dir.y > 0)
					texture_dir = south_tex;
				else
					texture_dir = north_tex;
			}
			line_height = (int)(g->window_size.y / g->dp.distance);
			draw_start = -line_height / 2 + g->window_size.y / 2;
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
			texX = (int)(wallX * (double)g->texture[texture_dir].dimensions.x);
			if ((g->dp.side == 0 && ray_dir.x > 0) || (g->dp.side == 1
					&& ray_dir.y < 0))
				texX = g->texture[texture_dir].dimensions.x - texX - 1;
			step = 1.0 * g->texture[texture_dir].dimensions.y / line_height;
			texPos = (draw_start - (double)g->window_size.y / 2
					+ (double)line_height / 2) * step;
			y = draw_start;
			while (y < draw_end)
			{
				texY = (int)texPos; //& (g->texture.dimensions.y - 1);
				texPos += step;
				// int	color = get_pixel_of_img(g->frame, (t_pixel_point){texX,
				//			texY});
				// if(g->dp.side == 1) color = (color >> 1) & 8355711; //
				put_pixel_on_img(&g->frame, (t_pixel_point){x, y},
					get_pixel_of_img(g->texture[texture_dir],
						(t_pixel_point){texX, texY}));
				y++;
			}
		}
		x++;
	}
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	// mlx_destroy_image(g->mlx, g->frame.img);
}
