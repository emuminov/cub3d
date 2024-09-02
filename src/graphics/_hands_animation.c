/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _hands_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:38:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 15:30:38 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/constants.h"
#include "../../include/graphics.h"
#include "../../include/cub3d.h"

void	render_animation(t_game *g, int frame_nb, t_img *texture)
{
	int	x;
	int	color;
	int	y;

	x = 0;
	while (x < g->window_size.x)
	{
		y = 0;
		while (y < g->window_size.y)
		{
			color = get_pixel_of_img(texture[frame_nb], (t_pixel_point){x, y});
			if (color != (int)0xFF000000)
				put_pixel_on_img(&g->frame, (t_pixel_point){x, y}, color);
			y++;
		}
		x++;
	}
}

static bool	is_move_key_pressed(t_game *g)
{
	return (g->controls.move_left_pressed || g->controls.move_right_pressed
		|| g->controls.move_down_pressed || g->controls.move_up_pressed);
}

void	render_hands(t_game *g)
{
	// static int	punch_frame;
	static int	idle_frame;
	static int	walk_frame;
	static int	idle_flower_frame;
	static int	walk_flower_frame;
	static int	flower_in_frame;
	static int	flower_out_frame;
	static int	frame;

	frame++;
	if (g->player.takes_flower)
	{
		if (g->player.has_flower)
		{
			idle_frame = 0;
			render_animation(g, flower_in_frame, g->flower_in_textures);
			if (!(frame % 5))
				flower_in_frame++;
			if (flower_in_frame == FLOWER_IN_LAST)
			{
				flower_in_frame = 0;
				g->player.takes_flower = false;
				g->player.has_flower = false;
			}
		}
		else
		{
			idle_frame = 0;
			render_animation(g, flower_out_frame, g->flower_out_textures);
			if (!(frame % 5))
				flower_out_frame++;
			if (flower_out_frame == FLOWER_OUT_LAST)
			{
				flower_out_frame = 0;
				g->player.takes_flower = false;
				g->player.has_flower = true;
			}
		}
	}
	else if (is_move_key_pressed(g))
	{
		if (g->player.has_flower)
		{
			idle_frame = 0;
			render_animation(g, walk_flower_frame, g->walk_flower_textures);
			if (!(frame % 5))
				walk_flower_frame++;
			if (walk_flower_frame == WALK_FLOWER_LAST)
				walk_flower_frame = 0;
		}
		else
		{
			idle_frame = 0;
			render_animation(g, walk_frame, g->walk_textures);
			if (!(frame % 5))
				walk_frame++;
			if (walk_frame == WALK_LAST)
				walk_frame = 0;
		}
	}
	else
	{
		if (g->player.has_flower)
		{
			walk_frame = 0;
			render_animation(g, idle_flower_frame, g->idle_flower_textures);
			if (!(frame % 10))
				idle_flower_frame++;
			if (idle_flower_frame == IDLE_FLOWER_LAST)
				idle_flower_frame = 0;
		}
		else
		{
			walk_frame = 0;
			render_animation(g, idle_frame, g->idle_textures);
			if (!(frame % 10))
				idle_frame++;
			if (idle_frame == IDLE_LAST)
				idle_frame = 0;
		}
	}
}
