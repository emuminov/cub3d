/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _movement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:07:41 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/28 13:55:58 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/constants.h"
#include "../../include/cub3d.h"
#include "../../include/math_funcs.h"

t_grid_coordsf	move_player(t_player p, const t_controls *controls)
{
	if (controls->move_left_pressed && controls->move_up_pressed)
		p.pos = vectorf_add(p.pos, vectorf_scale(vectorf_rotate(p.dir, -45),
					MOVEMENT_SPEED));
	else if (controls->move_right_pressed && controls->move_up_pressed)
		p.pos = vectorf_add(p.pos, vectorf_scale(vectorf_rotate(p.dir, 45),
					MOVEMENT_SPEED));
	else if (controls->move_left_pressed && controls->move_down_pressed)
		p.pos = vectorf_sub(p.pos, vectorf_scale(vectorf_rotate(p.dir, 45),
					MOVEMENT_SPEED));
	else if (controls->move_right_pressed && controls->move_down_pressed)
		p.pos = vectorf_sub(p.pos, vectorf_scale(vectorf_rotate(p.dir, -45),
					MOVEMENT_SPEED));
	else if (controls->move_up_pressed)
		p.pos = vectorf_add(p.pos, vectorf_scale(p.dir, MOVEMENT_SPEED));
	else if (controls->move_down_pressed)
		p.pos = vectorf_sub(p.pos, vectorf_scale(p.dir, MOVEMENT_SPEED));
	else if (controls->move_left_pressed)
		p.pos = vectorf_add(p.pos, vectorf_scale(vectorf_rotate(p.dir, -90),
					MOVEMENT_SPEED));
	else if (controls->move_right_pressed)
		p.pos = vectorf_add(p.pos, vectorf_scale(vectorf_rotate(p.dir, 90),
					MOVEMENT_SPEED));
	return (p.pos);
}

/* Gets the direction of player based on the key pressed */
t_vectorf	get_movement_dir(const t_controls *controls, const t_player *player)
{
	t_vectorf	dir;

	dir = (t_vectorf){.x = -1, .y = -1};
	if (controls->move_left_pressed && controls->move_up_pressed)
		dir = vectorf_rotate(player->dir, -45);
	else if (controls->move_right_pressed && controls->move_up_pressed)
		dir = vectorf_rotate(player->dir, 45);
	else if (controls->move_left_pressed && controls->move_down_pressed)
		dir = vectorf_rotate(player->dir, 225);
	else if (controls->move_right_pressed && controls->move_down_pressed)
		dir = vectorf_rotate(player->dir, -225);
	else if (controls->move_up_pressed)
		dir = player->dir;
	else if (controls->move_down_pressed)
		dir = vectorf_rotate(player->dir, 180);
	else if (controls->move_left_pressed)
		dir = vectorf_rotate(player->dir, -90);
	else if (controls->move_right_pressed)
		dir = vectorf_rotate(player->dir, 90);
	return (dir);
}

void	resolve_rotation(t_game *g)
{
	if (g->controls.rotate_left_pressed)
	{
		g->player.dir = vectorf_rotate(g->player.dir, -ROTATION_SPEED);
		g->player.plane = vectorf_rotate(g->player.plane, -ROTATION_SPEED);
	}
	else if (g->controls.rotate_right_pressed)
	{
		g->player.dir = vectorf_rotate(g->player.dir, ROTATION_SPEED);
		g->player.plane = vectorf_rotate(g->player.plane, ROTATION_SPEED);
	}
}

/* Collision is resolved using DDA which checks one grid in the direction of
 * movement of the player */
void	resolve_movement(t_game *g)
{
	const t_grid_coordsf	new_pos = move_player(g->player, &g->controls);
	const t_grid_coordsf	mdir = get_movement_dir(&g->controls, &g->player);
	const t_grid_coordsf	checked_pos = vectorf_add(new_pos,
			vectorf(PLAYER_SIZE * mdir.x, PLAYER_SIZE * mdir.y));

	check_cell_in_dir(g, mdir, 1, "1D");
	if (!g->dp.is_cell_found || !is_beyond(checked_pos, g->dp.last_cell,
				mdir))
		g->player.pos = new_pos;
}
