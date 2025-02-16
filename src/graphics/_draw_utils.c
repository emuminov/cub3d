/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _draw_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:30:48 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/28 13:59:25 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/constants.h"
#include "../../include/cub3d.h"
#include "../../include/graphics.h"
#include "../../include/math_funcs.h"
#include <math.h>
#include <stdlib.h>

/* Uses DDA line drawing algorithm. delta variable is reused after as
 * a placeholder for the rounded vector, to reduce the number of variables. */
void	draw_mininmap_line(t_img *frame, t_pixel_point start, t_pixel_point end,
		int color)
{
	t_pixel_point	delta;
	t_vectorf		next_point;
	t_vectorf		inc;
	int				steps;
	int				i;

	delta = vectori_sub(end, start);
	next_point = vectorf(start.x, start.y);
	steps = max(abs(delta.x), abs(delta.y));
	inc = vectorf((double)delta.x / steps, (double)delta.y / steps);
	i = 0;
	while (i < steps)
	{
		delta = vectori(round(next_point.x), round(next_point.y));
		put_pixel_on_img_bounds(frame, delta,
			get_transparent_color(MINIMAP_FOV_ALPHA, color,
				get_pixel_of_img_bounds(*frame, delta, frame->dimensions)),
			vectori(MINIMAP_SIZE, MINIMAP_SIZE));
		next_point.x += inc.x;
		next_point.y += inc.y;
		i++;
	}
}

void	draw_transparent_tile(t_img *frame, t_pixel_point p, int color,
		t_pixel_point bounds)
{
	t_pixel_point	start;
	t_pixel_point	end;

	start = p;
	end.x = p.x + MINIMAP_TILE_SIZE;
	end.y = p.y + MINIMAP_TILE_SIZE;
	while (start.y < end.y)
	{
		start.x = p.x;
		while (start.x < end.x)
		{
			if (start.x >= 0 && start.y >= 0)
				put_pixel_on_img_bounds(frame, start,
					get_transparent_color(MINIMAP_ALPHA, color,
						get_pixel_of_img(*frame, start)), bounds);
			start.x++;
		}
		start.y++;
	}
}

void	draw_square(t_img *frame, t_pixel_point pos, int size, int color)
{
	t_pixel_point	point;
	int				y;
	int				x;

	y = 0;
	while (y <= size)
	{
		x = 0;
		while (x <= size)
		{
			point.x = round((pos.x + x) - (double)size / 2);
			point.y = round((pos.y + y) - (double)size / 2);
			put_pixel_on_img_bounds(frame, point, color, frame->dimensions);
			x++;
		}
		y++;
	}
}

void	draw_tile_bounds(t_img *frame, t_pixel_point p, int color,
		t_pixel_point bounds)
{
	t_pixel_point	start;
	t_pixel_point	end;

	start = p;
	end.x = p.x + MINIMAP_TILE_SIZE;
	end.y = p.y + MINIMAP_TILE_SIZE;
	while (start.y < end.y)
	{
		start.x = p.x;
		while (start.x < end.x)
		{
			put_pixel_on_img_bounds(frame, start, color, bounds);
			start.x++;
		}
		start.y++;
	}
}

void	draw_ceiling_and_floor(t_img *frame, int ceiling_color, int floor_color)
{
	int				ceiling_end;
	t_pixel_point	p;

	ceiling_end = frame->dimensions.y / 2;
	p.y = -1;
	while (++p.y < ceiling_end)
	{
		p.x = -1;
		while (++p.x < frame->dimensions.x)
			put_pixel_on_img(frame, p, ceiling_color);
	}
	while (++p.y < frame->dimensions.y)
	{
		p.x = -1;
		while (++p.x < frame->dimensions.x)
			put_pixel_on_img(frame, p, floor_color);
	}
}
