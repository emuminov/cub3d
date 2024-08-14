/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:35:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 15:35:36 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_minimap(t_game *g)
{
	t_grid_coordsf	curr_grid;
	t_pixel_point	p;

	curr_grid = vectorf_round(vectorf_sub(g->player.pos, vectorf_scale(pixel_point_to_grid_coordsf(g->window_size), 0.5)));
	printf("%f %f\n", curr_grid.x, curr_grid.y);
	p.x = 0;
	p.y = 0;
	while (p.y < g->frame.dimensions.y)
	{
		while (p.x < g->frame.dimensions.x)
		{
			p.x++;
		}
		p.y++;
	}
}
