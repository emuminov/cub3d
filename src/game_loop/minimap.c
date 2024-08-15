/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:35:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/15 20:14:17 by emuminov         ###   ########.fr       */
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
	t_grid_coordsf	top_left_grid;
	t_grid_coordsi	start;
	t_grid_coordsi	end;
	// t_grid_coordsi	curr_grid;
	t_grid_coordsf	delta_start;
	t_grid_coordsf	delta_end;
	t_pixel_point	offset;

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
	printf("Is wall:                   %d\n", g->map[3][2] == '1');
	printf("Is wall:                   %d\n", g->map[1][2] == '1');

	for (int y = start.y; y < end.y; y++)
	{
		for (int x = start.x; x < end.x; x++)
		{
			t_pixel_point p;
			p = 320 + delta_start.x * 128;
			draw_minimap_tile(&g->frame, offset, 0xAA0000);
		}
	}
	draw_minimap_tile(&g->frame, offset, 0xAA0000);
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
