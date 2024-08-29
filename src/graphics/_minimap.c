/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:35:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/30 00:15:34 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/constants.h"
#include "../../include/cub3d.h"
#include "../../include/graphics.h"
#include "../../include/math_funcs.h"
#include <math.h>

static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
							t_grid_coordsf player_pos);
static void				draw_tiles_around_player(t_game *g,
							t_pixel_point offset, t_grid_coordsi start,
							t_grid_coordsi end);
static void				draw_tile_based_on_map(t_game *g, t_grid_coordsi c,
							t_pixel_point p, t_pixel_point bounds);
static bool				is_floor(t_game *g, t_grid_coordsi c);

void	draw_minimap(t_game *g)
{
	t_grid_coordsf	top_left_grid;
	t_grid_coordsi	start;
	t_grid_coordsi	end;
	int				x;

	check_cell_in_dir(g, g->player.dir, 100, "1D");
	top_left_grid = vectorf_sub(g->player.pos, (t_grid_coordsf){.x = 2.5,
			.y = 2.5});
	start.x = floor(top_left_grid.x);
	start.y = floor(top_left_grid.y);
	end.x = floor(top_left_grid.x + 5);
	end.y = floor(top_left_grid.y + 5);
	draw_tiles_around_player(g, calculate_pixel_offset(start, g->player.pos),
		start, end);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		draw_mininmap_line(&g->frame, vectori(MINIMAP_SIZE / 2,
				MINIMAP_SIZE / 2), grid_coordsf_to_pixel_point(
				vectorf_sub(g->rays[x], top_left_grid),
				MINIMAP_TILE_SIZE), 0xFFD700);
		x++;
	}
	draw_square(&g->frame, vectori(MINIMAP_SIZE / 2, MINIMAP_SIZE / 2), 25,
		0xAA00AA);
}

/* Calculates the pixel position of the start of visible tile.
 * It will be [0 0] if tile is fully visible, or one of the values will be
 * negative, which means that tile is visible only partially. */
static t_pixel_point	calculate_pixel_offset(t_grid_coordsi start,
		t_grid_coordsf player_pos)
{
	t_pixel_point	offset;
	t_grid_coordsf	delta_start;

	delta_start = (t_grid_coordsf){.x = start.x - player_pos.x, .y = start.y
		- player_pos.y};
	offset.x = (MINIMAP_SIZE * 0.5) + delta_start.x * MINIMAP_TILE_SIZE;
	offset.y = (MINIMAP_SIZE * 0.5) + delta_start.y * MINIMAP_TILE_SIZE;
	return (offset);
}

static bool	is_floor(t_game *g, t_grid_coordsi c)
{
	return (g->map[c.y][c.x] == empty || g->map[c.y][c.x] == player_east
		|| g->map[c.y][c.x] == player_west || g->map[c.y][c.x] == player_north
		|| g->map[c.y][c.x] == player_south);
}

static void	draw_tile_based_on_map(t_game *g, t_grid_coordsi c, t_pixel_point p,
		t_pixel_point bounds)
{
	if (c.y < 0 || c.x < 0 || c.y > (g->conf.map_size.y - 1)
		|| c.x > (g->len_tab[c.y]))
		draw_transparent_tile(&g->frame, p, 0x252525, bounds);
	else if (g->map[c.y][c.x] == wall)
		draw_tile_bounds(&g->frame, p, 0x555555, bounds);
	else if (g->map[c.y][c.x] == door_closed)
		draw_tile_bounds(&g->frame, p, 0x964B00, bounds);
	else if (g->map[c.y][c.x] == door_opened)
		draw_tile_bounds(&g->frame, p, 0x903000, bounds);
	else if (is_floor(g, c))
		draw_transparent_tile(&g->frame, p, 0xAAAAAA, bounds);
	else
		draw_transparent_tile(&g->frame, p, 0x252525, bounds);
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
