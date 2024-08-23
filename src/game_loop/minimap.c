/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:35:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/23 19:22:00 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
		t_grid_coordsf player_pos, int tile_size, t_pixel_point window_size);
static void	draw_tiles_around_player(t_game *g, t_pixel_point offset,
		t_grid_coordsi start, t_grid_coordsi end, int tile_size);

void	draw_2d_plane(t_game *g)
{
	t_grid_coordsf	top_left_grid;
	t_grid_coordsi	start;
	t_grid_coordsi	end;
	t_grid_coordsf	ray;

	ray = check_cell_in_dir(g, g->player.pos, g->player.dir, 100, "1D");
	top_left_grid = vectorf_sub(g->player.pos, (t_grid_coordsf){.x = 2.5, .y = 2.5});
	start.x = floor(top_left_grid.x);
	start.y = floor(top_left_grid.y);
	end.x = floor(top_left_grid.x + 5);
	end.y = floor(top_left_grid.y + 5);
	draw_tiles_around_player(g, calculate_pixel_offset(start, g->player.pos, 128, g->window_size),
			start, end, 128);
	draw_square(&g->frame, (t_pixel_point){.x = 320, .y = 320}, 25, 0xAA00AA);
	if (ray.x != -1)
	{
		draw_line(&g->frame, (t_pixel_point){.x = 320, .y = 320},
				grid_coordsf_to_pixel_point(vectorf_sub(ray, top_left_grid)), 0xAA00AA);
		draw_hollow_square(&g->frame, grid_coordsf_to_pixel_point(vectorf_sub(ray, top_left_grid)), 25,
				0x2AAA2A);
	}
}

void	draw_minimap(t_game *g)
{
	t_grid_coordsf	top_left_grid;
	t_grid_coordsi	start;
	t_grid_coordsi	end;
	t_grid_coordsf	ray;

	ray = check_cell_in_dir(g, g->player.pos, g->player.dir, 100, "1D");
	top_left_grid = vectorf_sub(g->player.pos, (t_grid_coordsf){.x = 2.5, .y = 2.5});
	start.x = floor(top_left_grid.x);
	start.y = floor(top_left_grid.y);
	end.x = floor(top_left_grid.x + 5);
	end.y = floor(top_left_grid.y + 5);
	draw_tiles_around_player(g, calculate_pixel_offset(start, g->player.pos, 128, g->window_size),
			start, end, 128);
	draw_square(&g->frame, (t_pixel_point){.x = g->minimap_size.x / 2,
			.y = g->minimap_size.y / 2}, 25, 0xAA00AA);
	if (ray.x != -1)
	{
		draw_line(&g->frame, (t_pixel_point){.x = g->minimap_size.x / 2, .y = g->minimap_size.y / 2},
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
				draw_tile(&g->frame, p, 0x000000, tile_size);
			else if (g->map[y][x] == wall)
				draw_tile(&g->frame, p, 0x555555, tile_size);
			else if (g->map[y][x] == empty || g->map[y][x] == '2')
				draw_tile(&g->frame, p, 0xAAAAAA, tile_size);
			else if (g->map[y][x] == door_closed)
				draw_tile(&g->frame, p, 0x964B00, tile_size);
			else if (g->map[y][x] == door_opened)
				draw_tile(&g->frame, p, 0x903000, tile_size);
			p.x += tile_size;
		}
		p.y += tile_size;
	}
}
