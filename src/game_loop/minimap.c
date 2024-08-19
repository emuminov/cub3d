/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:35:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/19 21:45:45 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
		t_grid_coordsf player_pos);
static void	draw_tiles_around_player(t_game *g, t_pixel_point offset,
		t_grid_coordsi start, t_grid_coordsi end);

void	draw_minimap(t_game *g)
{
	t_grid_coordsf	top_left_grid;
	t_grid_coordsi	start;
	t_grid_coordsi	end;
	t_grid_coordsf	ray;

	ray = check_wall_in_dir(g, &g->dp, g->player.pos, g->player.dir, 100);
	top_left_grid = vectorf_sub(g->player.pos, (t_grid_coordsf){.x = 2.5, .y = 2.5});
	start.x = floor(top_left_grid.x);
	start.y = floor(top_left_grid.y);
	end.x = floor(top_left_grid.x + 5);
	end.y = floor(top_left_grid.y + 5);
	draw_tiles_around_player(g, calculate_pixel_offset(start, g->player.pos),
			start, end);
	draw_square(&g->frame, (t_pixel_point){.x = 320, .y = 320}, 25, 0xAA00AA);
	if (ray.x != -1)
	{
		draw_line(&g->frame, (t_pixel_point){.x = 320, .y = 320},
				grid_coordsf_to_pixel_point(vectorf_sub(ray, top_left_grid)), 0xAA00AA);
		draw_hollow_square(&g->frame, grid_coordsf_to_pixel_point(vectorf_sub(ray, top_left_grid)), 25,
				0x2AAA2A);
	}
}

/* Calculates the pixel position of the start of visible tile.
 * It will be [0 0] if tile is fully visible, or one of the values will be
 * negative, which means that tile is visible only partially. */
// TODO: replace hardcoded values
static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
		t_grid_coordsf player_pos)
{
	t_pixel_point	offset;
	t_grid_coordsf	delta_start;

	delta_start = (t_grid_coordsf){
		.x = start.x - player_pos.x,
		.y = start.y - player_pos.y
	};
	offset.x = 320 + delta_start.x * TILE_SIZE;
	offset.y = 320 + delta_start.y * TILE_SIZE;
	return (offset);
}

// TODO: replace hardcoded values
static void	draw_tiles_around_player(t_game *g, t_pixel_point offset,
		t_grid_coordsi start, t_grid_coordsi end)
{
	t_pixel_point	p;

	p = offset;
	for (int y = start.y; y <= end.y; y++)
	{
		p.x = offset.x;
		for (int x = start.x; x <= end.x; x++)
		{
			if (y < 0 || x < 0 || y > (g->map_size.y - 1) || x > (g->map_size.x - 1))
				draw_tile(&g->frame, p, 0x000000);
			else if (g->map[y][x] == '1')
				draw_tile(&g->frame, p, 0x555555);
			else if (g->map[y][x] == '0' || g->map[y][x] == '2')
				draw_tile(&g->frame, p, 0xAAAAAA);
			p.x += TILE_SIZE;
		}
		p.y += TILE_SIZE;
	}
}
