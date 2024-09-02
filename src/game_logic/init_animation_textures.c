/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animation_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:04:36 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 18:56:44 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/game_logic.h"

static int	init_idle_textures(t_game *g);
static int	init_walk_textures(t_game *g);
static int	init_flower_out_textures(t_game *g);
static int	init_flower_in_textures(t_game *g);

int	init_animation_textures(t_game *g)
{
	if (init_idle_textures(g) == 1
		|| init_walk_textures(g) == 1
		|| init_flower_out_textures(g) == 1
		|| init_flower_in_textures(g) == 1)
		return (1);
	return (0);
}

static int	init_idle_textures(t_game *g)
{
	init_texture(g, &g->idle_textures[0], IDLE_0);
	init_texture(g, &g->idle_textures[1], IDLE_1);
	init_texture(g, &g->idle_textures[2], IDLE_2);
	init_texture(g, &g->idle_textures[3], IDLE_3);
	init_texture(g, &g->idle_textures[4], IDLE_4);
	init_texture(g, &g->idle_textures[5], IDLE_5);
	if (!textures_are_valid(g->idle_textures, IDLE_FRAMES))
		return (1);
	init_texture(g, &g->idle_flower_textures[0], IDLE_FLOWER_0);
	init_texture(g, &g->idle_flower_textures[1], IDLE_FLOWER_1);
	init_texture(g, &g->idle_flower_textures[2], IDLE_FLOWER_2);
	init_texture(g, &g->idle_flower_textures[3], IDLE_FLOWER_3);
	init_texture(g, &g->idle_flower_textures[4], IDLE_FLOWER_4);
	init_texture(g, &g->idle_flower_textures[5], IDLE_FLOWER_5);
	if (!textures_are_valid(g->idle_flower_textures, IDLE_FLOWER_FRAMES))
		return (1);
	return (0);
}

static int	init_walk_textures(t_game *g)
{
	init_texture(g, &g->walk_textures[0], WALK_0);
	init_texture(g, &g->walk_textures[1], WALK_1);
	init_texture(g, &g->walk_textures[2], WALK_2);
	init_texture(g, &g->walk_textures[3], WALK_3);
	init_texture(g, &g->walk_textures[4], WALK_4);
	init_texture(g, &g->walk_textures[5], WALK_5);
	init_texture(g, &g->walk_textures[6], WALK_6);
	init_texture(g, &g->walk_textures[7], WALK_7);
	if (!textures_are_valid(g->walk_textures, WALK_FRAMES))
		return (1);
	init_texture(g, &g->walk_flower_textures[0], WALK_FLOWER_0);
	init_texture(g, &g->walk_flower_textures[1], WALK_FLOWER_1);
	init_texture(g, &g->walk_flower_textures[2], WALK_FLOWER_2);
	init_texture(g, &g->walk_flower_textures[3], WALK_FLOWER_3);
	init_texture(g, &g->walk_flower_textures[4], WALK_FLOWER_4);
	init_texture(g, &g->walk_flower_textures[5], WALK_FLOWER_5);
	init_texture(g, &g->walk_flower_textures[6], WALK_FLOWER_6);
	init_texture(g, &g->walk_flower_textures[7], WALK_FLOWER_7);
	if (!textures_are_valid(g->walk_flower_textures, WALK_FLOWER_FRAMES))
		return (1);
	return (0);
}

static int	init_flower_out_textures(t_game *g)
{
	init_texture(g, &g->flower_out_textures[0], FLOWER_OUT_00);
	init_texture(g, &g->flower_out_textures[1], FLOWER_OUT_01);
	init_texture(g, &g->flower_out_textures[2], FLOWER_OUT_02);
	init_texture(g, &g->flower_out_textures[3], FLOWER_OUT_03);
	init_texture(g, &g->flower_out_textures[4], FLOWER_OUT_04);
	init_texture(g, &g->flower_out_textures[5], FLOWER_OUT_05);
	init_texture(g, &g->flower_out_textures[6], FLOWER_OUT_06);
	init_texture(g, &g->flower_out_textures[7], FLOWER_OUT_07);
	init_texture(g, &g->flower_out_textures[8], FLOWER_OUT_08);
	init_texture(g, &g->flower_out_textures[9], FLOWER_OUT_09);
	init_texture(g, &g->flower_out_textures[10], FLOWER_OUT_10);
	init_texture(g, &g->flower_out_textures[11], FLOWER_OUT_11);
	if (!textures_are_valid(g->flower_out_textures, FLOWER_OUT_FRAMES))
		return (1);
	return (0);
}

static int	init_flower_in_textures(t_game *g)
{
	init_texture(g, &g->flower_in_textures[0], FLOWER_IN_00);
	init_texture(g, &g->flower_in_textures[1], FLOWER_IN_01);
	init_texture(g, &g->flower_in_textures[2], FLOWER_IN_02);
	init_texture(g, &g->flower_in_textures[3], FLOWER_IN_03);
	init_texture(g, &g->flower_in_textures[4], FLOWER_IN_04);
	init_texture(g, &g->flower_in_textures[5], FLOWER_IN_05);
	init_texture(g, &g->flower_in_textures[6], FLOWER_IN_06);
	init_texture(g, &g->flower_in_textures[7], FLOWER_IN_07);
	init_texture(g, &g->flower_in_textures[8], FLOWER_IN_08);
	init_texture(g, &g->flower_in_textures[9], FLOWER_IN_09);
	init_texture(g, &g->flower_in_textures[10], FLOWER_IN_10);
	if (!textures_are_valid(g->flower_in_textures, FLOWER_IN_FRAMES))
		return (1);
	return (0);
}
