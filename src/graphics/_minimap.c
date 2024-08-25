/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:35:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 00:28:37 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/graphics.h"
#include "../../include/math_funcs.h"
#include "../../include/constants.h"
#include <math.h>

static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
		t_grid_coordsf player_pos, int tile_size, t_pixel_point window_size);
static void	draw_tiles_around_player(t_game *g, t_pixel_point offset,
		t_grid_coordsi start, t_grid_coordsi end,
		int tile_size);

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
	draw_tiles_around_player(g, calculate_pixel_offset(start, g->player.pos, MINIMAP_TILE_SIZE, g->minimap_size),
			start, end, MINIMAP_TILE_SIZE);
	draw_square(&g->frame, (t_pixel_point){.x = g->minimap_size.x / 2,
			.y = g->minimap_size.y / 2}, 25, 0xAA00AA);
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
// TODO: replace hardcoded values
static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
		t_grid_coordsf player_pos, int tile_size, t_pixel_point window_size)
{
	t_pixel_point	offset;
	t_grid_coordsf	delta_start;

	delta_start = (t_grid_coordsf){
		.x = start.x - player_pos.x,
		.y = start.y - player_pos.y
	};
	offset.x = (window_size.x * 0.5) + delta_start.x * tile_size;
	offset.y = (window_size.y * 0.5) + delta_start.y * tile_size;
	return (offset);
}

void	draw_transparent_tile(t_img *frame, t_pixel_point p, int color,
		int tile_size, t_pixel_point bounds)
{
	t_pixel_point	start;
	t_pixel_point	end;

	start = p;
	end.x = p.x + tile_size;
	end.y = p.y + tile_size;
	while (start.y < end.y)
	{
		start.x = p.x;
		while (start.x < end.x)
		{
			if (start.x >= 0 && start.y >= 0)
				put_pixel_on_img_bounds(frame, start, get_transparent_color(200, color,
						get_pixel_of_img(*frame, start)), bounds);
			start.x++;
		}
		start.y++;
	}
}

// TODO: replace hardcoded values
static void	draw_tiles_around_player(t_game *g, t_pixel_point offset,
		t_grid_coordsi start, t_grid_coordsi end, int tile_size)
{
	t_pixel_point	p;

	p = offset;
	for (int y = start.y; y <= end.y; y++)
	{
		p.x = offset.x;
		for (int x = start.x; x <= end.x; x++)
		{
			if (y < 0 || x < 0 || y > (g->map_size.y - 1) || x > (g->map_size.x - 1))
				draw_transparent_tile(&g->frame,  p, 0x252525, tile_size, g->minimap_size);
			else if (g->map[y][x] == wall)
				draw_tile_bounds(&g->frame, p, 0x555555, tile_size, g->minimap_size);
			else if (g->map[y][x] == empty || g->map[y][x] == '2')
				draw_transparent_tile(&g->frame,  p, 0xAAAAAA,tile_size, g->minimap_size);
			else if (g->map[y][x] == door_closed)
				draw_tile_bounds(&g->frame, p, 0x964B00, tile_size, g->minimap_size);
			else if (g->map[y][x] == door_opened)
				draw_tile_bounds(&g->frame, p, 0x903000, tile_size, g->minimap_size);
			p.x += tile_size;
		}
		p.y += tile_size;
	}
}
