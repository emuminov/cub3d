/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _hands_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:38:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 13:23:47 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/constants.h"
#include "../../include/graphics.h"
#include "../../include/cub3d.h"

void	render_idle_animation(t_game *g, int frame_nb, t_img *texture)
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
	static int	flower_idle_frame;
	static int	flower_walk_frame;
	static int	flower_in_frame;
	static int	flower_out_frame;
	static int	frame;

	frame++;
	if (is_move_key_pressed(g))
	{
		idle_frame = 0;
		render_idle_animation(g, walk_frame, g->walk_textures);
		if (!(frame % 5))
			walk_frame++;
		if (walk_frame == WALK_FRAMES)
			walk_frame = 0;
	}
	else
	{
		walk_frame = 0;
		render_idle_animation(g, idle_frame, g->idle_textures);
		if (!(frame % 10))
			idle_frame++;
		if (idle_frame == IDLE_FRAMES)
			idle_frame = 0;
	}
}
