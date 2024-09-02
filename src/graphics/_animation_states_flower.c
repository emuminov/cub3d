/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:50:23 by eandre            #+#    #+#             */
/*   Updated: 2024/09/02 19:52:24 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/constants.h"
#include "../../include/graphics.h"
#include "../../include/cub3d.h"

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
