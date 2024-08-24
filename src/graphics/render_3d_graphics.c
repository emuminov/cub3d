/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:42:10 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 00:30:36 by emuminov         ###   ########.fr       */
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

	draw_ceiling_and_floor(&g->frame, g->conf.ceiling_c, g->conf.floor_c);
	x = 0;
	while (x < g->window_size.x)
	{
		cam_x = 2 * x / (double)g->window_size.x - 1;
		ray_dir = vectorf_add(g->player.dir, vectorf_scale(g->player.plane, cam_x));
		ray = check_cell_in_dir(g, g->player.pos, ray_dir, 100, "1D");
		if (ray.x != -1)
		{
			line_height = (int)(g->window_size.y / g->dp.distance);
			draw_start = -line_height / 2 + g->window_size.y / 2;
			if (draw_start < 0)
				draw_start = 0;
			draw_end = line_height / 2 + g->window_size.y / 2;
			if (draw_end >= g->window_size.y)
				draw_end = g->window_size.y - 1;
			double wallX;
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
			double texPos = (draw_start - g->window_size.y / 2 + line_height / 2) * step;
			y = draw_start;
			while (y < draw_end)
			{
				int texY = (int)texPos; //& (g->texture.dimensions.y - 1);
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
// mlx_destroy_image(g->mlx, g->frame.img);
}
