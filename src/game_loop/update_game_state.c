/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:25:35 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/20 20:06:29 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	update_game_state(t_game *g)
{
	g->player.collision_point = (t_grid_coordsf){.x = -1, .y = -1};
	if (is_any_key_pressed(g))
	{
		resolve_rotation(g);
		resolve_movement(g);
	}
}
