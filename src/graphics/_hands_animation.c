/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _hands_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:38:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 17:14:01 by eandre           ###   ########.fr       */
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

void	render_flower_in(t_game *g, int *walk_f, int *idle_f, int *frame)
{
	static int	flower_in_frame;

	*idle_f = 0;
	*walk_f = 0;
	render_animation(g, flower_in_frame, g->flower_in_textures);
	if (!(*frame % 5))
		flower_in_frame++;
	if (flower_in_frame == FLOWER_IN_LAST)
	{
		flower_in_frame = 0;
		g->player.takes_flower = false;
		g->player.has_flower = false;
	}
}

void	render_flower_out(t_game *g, int *walk_f, int *idle_f, int *frame)
{
	static int	flower_out_frame;

	*idle_f = 0;
	*walk_f = 0;
	render_animation(g, flower_out_frame, g->flower_out_textures);
	if (!(*frame % 5))
		flower_out_frame++;
	if (flower_out_frame == FLOWER_OUT_LAST)
	{
		flower_out_frame = 0;
		g->player.takes_flower = false;
		g->player.has_flower = true;
	}
}

void	render_flower_interaction(t_game *g, int *walk_f, int *idle_f
, int *frame)
{
	if (g->player.has_flower)
		render_flower_in(g, walk_f, idle_f, frame);
	else
		render_flower_out(g, walk_f, idle_f, frame);
}

void	render_walk(t_game *g, int *walk_f, int *idle_f, int *frame)
{
	*idle_f = 0;
	render_animation(g, *walk_f, g->walk_textures);
	if (!(*frame % 5))
		(*walk_f)++;
	if (*walk_f == WALK_LAST)
		*walk_f = 0;
}

void	render_walk_flower(t_game *g, int *walk_flower_f, int *idle_flower_f
, int *frame)
{
	*idle_flower_f = 0;
	render_animation(g, *walk_flower_f, g->walk_flower_textures);
	if (!(*frame % 5))
		(*walk_flower_f)++;
	if (*walk_flower_f == WALK_FLOWER_LAST)
		*walk_flower_f = 0;
}

void	render_idle(t_game *g, int *walk_f, int *idle_f, int *frame)
{
	*walk_f = 0;
	render_animation(g, *idle_f, g->idle_textures);
	if (!(*frame % 10))
		(*idle_f)++;
	if (*idle_f == IDLE_LAST)
		*idle_f = 0;
}

void	render_idle_flower(t_game *g, int *walk_flower_f, int *idle_flower_f
, int *frame)
{
	*walk_flower_f = 0;
	render_animation(g, *idle_flower_f, g->idle_flower_textures);
	if (!(*frame % 10))
		(*idle_flower_f)++;
	if (*idle_flower_f == IDLE_FLOWER_LAST)
		*idle_flower_f = 0;
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
