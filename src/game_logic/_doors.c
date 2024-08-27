/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _doors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:06:07 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/27 17:59:08 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	toggle_door(t_game *g)
{
	t_grid_coordsf	ray;

	if (g->map[(int)g->player.pos.y][(int)g->player.pos.x] == door_opened
		|| g->map[(int)g->player.pos.y][(int)g->player.pos.x] == door_closed)
		return ;
	ray = check_cell_in_dir(g, g->player.pos, g->player.dir, 1, "DO");
	(void)ray;
	if (g->dp.distance > 0.75 || g->dp.type_of_found_cell == wall)
		return ;
	if (g->dp.type_of_found_cell == door_closed)
		g->map[g->dp.inspected_grid.y][g->dp.inspected_grid.x] = door_opened;
	else if (g->dp.type_of_found_cell == door_opened)
		g->map[g->dp.inspected_grid.y][g->dp.inspected_grid.x] = door_closed;
}
