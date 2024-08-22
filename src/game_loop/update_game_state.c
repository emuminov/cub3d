/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:25:35 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/22 18:10:07 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	update_game_state(t_game *g)
{
	g->player.collision_point = (t_grid_coordsf){.x = -1, .y = -1};
	// handle_mouse(g);
	if (is_any_key_pressed(g))
	{
		resolve_rotation(g);
		resolve_movement(g);
	}
}
