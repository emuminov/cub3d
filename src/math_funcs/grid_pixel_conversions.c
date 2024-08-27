/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_pixel_conversions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:39 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/28 01:30:09 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

t_pixel_point	grid_coordsf_to_pixel_point(t_grid_coordsf v, int tile_size)
{
	return ((t_pixel_point){.x = round(v.x * tile_size), .y = round(v.y
			* tile_size)});
}

t_pixel_point	grid_coordsi_to_pixel_point(t_grid_coordsi v, int tile_size)
{
	return ((t_pixel_point){.x = v.x * tile_size, .y = v.y * tile_size});
}

t_grid_coordsf	pixel_point_to_grid_coordsf(t_pixel_point v, int tile_size)
{
	return ((t_grid_coordsf){.x = (double)v.x / tile_size, .y = (double)v.y
		/ tile_size});
}

t_grid_coordsi	pixel_point_to_grid_coordsi(t_pixel_point v, int tile_size)
{
	return ((t_grid_coordsi){.x = v.x / tile_size, .y = v.y / tile_size});
}
