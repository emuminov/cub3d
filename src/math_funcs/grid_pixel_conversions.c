/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_pixel_conversions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:39 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 15:17:45 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

t_pixel_point	grid_coordsf_to_pixel_point(t_grid_coordsf v)
{
	return ((t_pixel_point){.x = round(v.x * TILE_SIZE), .y = round(v.y
			* TILE_SIZE)});
}

t_pixel_point	grid_coordsi_to_pixel_point(t_grid_coordsi v)
{
	return ((t_pixel_point){.x = v.x * TILE_SIZE, .y = v.y * TILE_SIZE});
}

t_grid_coordsf	pixel_point_to_grid_coordsf(t_pixel_point v)
{
	return ((t_grid_coordsf){.x = (double)v.x / TILE_SIZE, .y = (double)v.y
		/ TILE_SIZE});
}

t_grid_coordsi	pixel_point_to_grid_coordsi(t_pixel_point v)
{
	return ((t_grid_coordsi){.x = v.x / TILE_SIZE, .y = v.y / TILE_SIZE});
}
