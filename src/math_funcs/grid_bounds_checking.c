/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_bounds_checking.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:17:33 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/20 18:54:41 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_in_bounds_of_grid(t_grid_coordsi v, t_grid_coordsi map_size)
{
	return (!(v.x < 0 || v.x > (map_size.x - 1) || v.y < 0 || v.y > (map_size.y
				- 1)));
}

/* Checks if v1 goes further than v2 in the direction dir */
bool	is_beyond(t_grid_coordsf v1, t_grid_coordsf v2, t_vectorf dir)
{
	if (dir.x < 0 && dir.y >= 0)
		return (v1.x < v2.x || v1.y > v2.y);
	if (dir.x < 0 && dir.y < 0)
		return (v1.x < v2.x || v1.y < v2.y);
	if (dir.x >= 0 && dir.y >= 0)
		return (v1.x > v2.x || v1.y > v2.y);
	if (dir.x >= 0 && dir.y < 0)
		return (v1.x > v2.x || v1.y < v2.y);
	return (1);
}
