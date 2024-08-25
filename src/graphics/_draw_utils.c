/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _draw_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:30:48 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 02:45:43 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/graphics.h"
#include "../../include/math_funcs.h"
#include <math.h>
#include <stdlib.h>

/* DDA line drawing algorithm */
void	draw_line(t_img *frame, t_pixel_point start, t_pixel_point end,
		int color)
{
	const t_pixel_point	delta = vectori_sub(end, start);
	const int			steps = max(abs(delta.x), abs(delta.y));
	t_vectorf			next_point;
	t_vectorf			inc;
	int					i;

	next_point = (t_vectorf){.x = start.x, .y = start.y};
	inc = (t_vectorf){.x = (double)delta.x / steps, .y = (double)delta.y
		/ steps};
	i = 0;
	while (i < steps)
	{
		put_pixel_on_img_bounds(frame, (t_pixel_point){.x = round(next_point.x),
			.y = round(next_point.y)}, color, frame->dimensions);
		next_point.x += inc.x;
		next_point.y += inc.y;
		i++;
	}
}

void	draw_hollow_square(t_img *frame, t_pixel_point pos, int size, int color)
{
	int				i;
	t_pixel_point	point;

	i = 0;
	while (i <= size)
	{
		point.x = round((pos.x + i) - (double)size / 2);
		point.y = round((pos.y) - (double)size / 2);
		put_pixel_on_img_bounds(frame, point, color, frame->dimensions);
		point.x = round((pos.x) - (double)size / 2);
		point.y = round((pos.y + i) - (double)size / 2);
		put_pixel_on_img_bounds(frame, point, color, frame->dimensions);
		point.x = round((pos.x + size) - (double)size / 2);
		point.y = round((pos.y + i) - (double)size / 2);
		put_pixel_on_img_bounds(frame, point, color, frame->dimensions);
		point.x = round((pos.x + i) - (double)size / 2);
		point.y = round((pos.y + size) - (double)size / 2);
		put_pixel_on_img_bounds(frame, point, color, frame->dimensions);
		i++;
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

void	draw_tile_bounds(t_img *frame, t_pixel_point p, int color, int
		tile_size, t_pixel_point bounds)
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
