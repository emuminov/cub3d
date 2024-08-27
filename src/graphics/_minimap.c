/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:35:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/27 14:50:06 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/graphics.h"
#include "../../include/math_funcs.h"
#include "../../include/constants.h"
#include <math.h>

static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
		t_grid_coordsf player_pos);
static void				draw_tiles_around_player(t_game *g,
		t_pixel_point offset, t_grid_coordsi start, t_grid_coordsi end);
static void				draw_tile_based_on_map(t_game *g, t_grid_coordsi c,
		t_pixel_point p, t_pixel_point bounds);

void	draw_minimap(t_game *g)
{
	t_grid_coordsf	top_left_grid;
	t_grid_coordsi	start;
	t_grid_coordsi	end;

	top_left_grid = vectorf_sub(g->player.pos, (t_grid_coordsf){.x = 2.5, .y = 2.5});
	start.x = floor(top_left_grid.x);
	start.y = floor(top_left_grid.y);
	end.x = floor(top_left_grid.x + 5);
	end.y = floor(top_left_grid.y + 5);
	draw_tiles_around_player(g, calculate_pixel_offset(start, g->player.pos),
			start, end);
	draw_square(&g->frame, vectori(MINIMAP_SIZE / 2, MINIMAP_SIZE / 2), 25,
			0xAA00AA);
	// if (ray.x != -1)
	// {
	// 	draw_line(&g->frame, (t_pixel_point){.x = 320, .y = 320},
	// 			grid_coordsf_to_pixel_point(vectorf_sub(ray, top_left_grid)), 0xAA00AA);
	// 	draw_hollow_square(&g->frame, grid_coordsf_to_pixel_point(vectorf_sub(ray, top_left_grid)), 25,
	// 			0x2AAA2A);
	// }
}

/* Calculates the pixel position of the start of visible tile.
 * It will be [0 0] if tile is fully visible, or one of the values will be
 * negative, which means that tile is visible only partially. */
static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
		t_grid_coordsf player_pos)
{
	t_pixel_point	offset;
	t_grid_coordsf	delta_start;

	delta_start = (t_grid_coordsf){
		.x = start.x - player_pos.x,
		.y = start.y - player_pos.y
	};
	offset.x = (MINIMAP_SIZE * 0.5) + delta_start.x * MINIMAP_TILE_SIZE;
	offset.y = (MINIMAP_SIZE * 0.5) + delta_start.y * MINIMAP_TILE_SIZE;
	return (offset);
}

static void	draw_tile_based_on_map(t_game *g, t_grid_coordsi c,
		t_pixel_point p, t_pixel_point bounds)
{
	if (c.y < 0 || c.x < 0 || c.y > (g->conf.map_size.y - 1)
			|| c.x > (g->conf.map_size.x - 1))
		draw_transparent_tile(&g->frame, p, 0x252525, MINIMAP_TILE_SIZE,
				bounds);
	else if (g->map[c.y][c.x] == wall)
		draw_tile_bounds(&g->frame, p, 0x555555, MINIMAP_TILE_SIZE, bounds);
	else if (g->map[c.y][c.x] == door_closed)
		draw_tile_bounds(&g->frame, p, 0x964B00, MINIMAP_TILE_SIZE, bounds);
	else if (g->map[c.y][c.x] == door_opened)
		draw_tile_bounds(&g->frame, p, 0x903000, MINIMAP_TILE_SIZE, bounds);
	else
		draw_transparent_tile(&g->frame, p, 0xAAAAAA, MINIMAP_TILE_SIZE,
				bounds);
}

static void	draw_tiles_around_player(t_game *g, t_pixel_point offset,
		t_grid_coordsi start, t_grid_coordsi end)
{
	t_pixel_point	p;
	t_pixel_point	bounds;
	int				y;
	int				x;

	bounds = vectori(MINIMAP_SIZE, MINIMAP_SIZE);
	p = offset;
	y = start.y;
	while (y <= end.y)
	{
		p.x = offset.x;
		x = start.x;
		while (x <= end.x)
		{
			draw_tile_based_on_map(g, vectori(x, y), p, bounds);
			p.x += MINIMAP_TILE_SIZE;
			x++;
		}
		p.y += MINIMAP_TILE_SIZE;
		y++;
	}
}
