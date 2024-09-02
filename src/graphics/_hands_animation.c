/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _hands_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:38:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 19:54:46 by eandre           ###   ########.fr       */
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
	static int	idle_f;
	static int	walk_f;
	static int	idle_flower_f;
	static int	walk_flower_f;
	static int	frame;

	frame++;
	if (g->player.takes_flower)
	{
		render_flower_interaction(g, &walk_f, &idle_f, &frame);
	}
	else if (is_move_key_pressed(g))
	{
		if (g->player.has_flower)
			render_walk_flower(g, &walk_flower_f, &idle_flower_f, &frame);
		else
			render_walk(g, &walk_f, &idle_f, &frame);
	}
	else
	{
		if (g->player.has_flower)
			render_idle_flower(g, &walk_flower_f, &idle_flower_f, &frame);
		else
			render_idle(g, &walk_f, &idle_f, &frame);
	}
}
