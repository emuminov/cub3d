/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:35:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/17 01:36:07 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

static void	draw_minimap_tile(t_img *frame, t_pixel_point p, int color);

// delta     - difference between top-left cell and the player
// start     - inclusive, start of the range of visible grid cells
// end       - exclusive, start of the range of visible grid cells
// curr_grid - currently instected grid
// NOTE: end can be floored instead of ceiled, maybe it will make it inclusive?
/* Calculated start is inclusive, calculated end is exclusive */
void	draw_minimap(t_game *g)
{
	volatile t_grid_coordsf	top_left_grid;
	volatile t_grid_coordsi	start;
volatile 	t_grid_coordsi	end;
	// t_grid_coordsi	curr_grid;
	volatile t_grid_coordsf	delta_start;
	volatile t_grid_coordsf	delta_end;
	volatile t_pixel_point	offset;
	volatile t_grid_coordsf	ray;

	// if (is_any_key_pressed(g))
	// {
		ray = check_wall_in_dir(g, &g->dp, g->player.pos, g->player.dir, 100);

		top_left_grid = vectorf_sub(g->player.pos, (t_grid_coordsf){.x = 2.5, .y = 2.5});
		start.x = floor(top_left_grid.x);
		start.y = floor(top_left_grid.y);
		end.x = ceil(top_left_grid.x + 5);
		end.y = ceil(top_left_grid.y + 5);
		// curr_grid = start;
		delta_start = (t_grid_coordsf){.x = start.x - g->player.pos.x, .y = start.y - g->player.pos.y};
		delta_end = (t_grid_coordsf){.x = g->player.pos.x - end.x, .y = g->player.pos.y - end.y};

		offset.x = 320 + delta_start.x * 128;
		offset.y = 320 + delta_start.y * 128;

		printf("Top left grid:             %f %f\n", top_left_grid.x, top_left_grid.y);
		printf("Start:                     %d %d\n", start.x, start.y);
		printf("End:                       %d %d\n", end.x, end.y);
		printf("Delta start:               %f %f\n", delta_start.x, delta_start.y);
		printf("Delta end:                 %f %f\n", delta_end.x, delta_end.y);
		printf("Offset:                    %d %d\n", offset.x, offset.y);
		printf("Ray:                       %f %f\n", ray.x, ray.y);
		printf("Player:                    %f %f\n", g->player.pos.x, g->player.pos.y);

		volatile t_pixel_point p;
		p = offset;
		for (int y = start.y; y < end.y; y++)
		{
			p.x = offset.x;
			for (int x = start.x; x < end.x; x++)
			{
				if (y < 0 || x < 0 || y > (g->map_size.y - 1) || x > (g->map_size.x - 1))
					draw_minimap_tile(&g->frame, p, 0x000000);
				else if (g->map[y][x] == '1')
					draw_minimap_tile(&g->frame, p, 0x555555);
				else if (g->map[y][x] == '0' || g->map[y][x] == '2')
					draw_minimap_tile(&g->frame, p, 0xAAAAAA);
				p.x += 128;
			}
			p.y += 128;
		}
		draw_square(&g->frame, (t_pixel_point){.x = 320, .y = 320}, 25, 0xAA00AA);
		if (ray.x != -1)
		{
			draw_line(&g->frame, (t_pixel_point){.x = 320, .y = 320},
					grid_coordsf_to_pixel_point(vectorf_sub(ray, top_left_grid)), 0xAA00AA);
			draw_hollow_square(&g->frame, grid_coordsf_to_pixel_point(vectorf_sub(ray, top_left_grid)), 25,
					0x2AAA2A);
		}
	// }
}

// void	draw_minimap(t_game *g) {
// 	t_grid_coordsf	top_left_grid;
// 	t_grid_coordsi	start;
// 	t_grid_coordsi	end;
// 	// t_grid_coordsi	curr_grid;
// 	// t_grid_coordsi	delta_start;
// 	// t_grid_coordsi	delta_end;
//
// 	top_left_grid = vectorf_sub(g->player.pos, (t_grid_coordsf){.x = 2.5, .y = 2.5});
// 	start.x = floor(top_left_grid.x);
// 	start.y = floor(top_left_grid.y);
// 	end.x = ceil(top_left_grid.x + 5);
// 	end.y = ceil(top_left_grid.y + 5);
// 	
// }

static void	draw_minimap_tile(t_img *frame, t_pixel_point p, int color)
{
	t_pixel_point	start;
	t_pixel_point	end;

	start = p;
	end.x = p.x + 128;
	end.y = p.y + 128;
	while (start.y < end.y)
	{
		start.x = p.x;
		while (start.x < end.x)
		{
			put_pixel_on_img(frame, start, color);
			start.x++;
		}
		start.y++;
	}
}
