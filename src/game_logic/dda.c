/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:01 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 02:48:29 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/math_funcs.h"
#include "../libft/libft.h"

static void	set_initial_dda_params(t_dda_params *dp, t_grid_coordsf start,
				t_vectorf dir, double max_distance);
static void	check_next_grid_cell(t_dda_params *dp);

/* DDA algorithm for finding the nearest wall in the certain direction */
t_vectorf	check_cell_in_dir(t_game *g, t_grid_coordsf start,
		t_vectorf dir, double max_distance, char *checked_tiles)
{
	t_vectorf	intersection;

	set_initial_dda_params(&g->dp, start, dir, max_distance);
	while (!g->dp.found_cell && g->dp.distance < g->dp.max_distance)
	{
		check_next_grid_cell(&g->dp);
		if (is_in_bounds_of_grid(g->dp.inspected_grid, g->map_size))
		{
			if (ft_strchr(checked_tiles, g->map[g->dp.inspected_grid.y][g->dp.inspected_grid.x]))
			{
				g->dp.found_cell = true;
				g->dp.type_of_found_cell = g->map[g->dp.inspected_grid.y][g->dp.inspected_grid.x];
			}
		}
		else
			break ;
	}
	if (g->dp.found_cell)
		intersection = vectorf_add(start, vectorf_scale(dir, g->dp.distance));
	else
		intersection = (t_grid_coordsf){.x = -1, .y = -1};
	return (intersection);
}

static void	set_initial_dda_params(t_dda_params *dp, t_grid_coordsf start,
		t_vectorf dir, double max_distance)
{
	dp->rate_of_change.x = abs_f(1 / dir.x);
	dp->rate_of_change.y = abs_f(1 / dir.y);
	dp->inspected_grid = (t_grid_coordsi){.x = start.x, .y = start.y};
	dp->ray_step.x = sign_f(dir.x);
	dp->ray_step.y = sign_f(dir.y);
	if (dir.x < 0)
		dp->dist_until_grid_side.x = (start.x - dp->inspected_grid.x)
			* dp->rate_of_change.x;
	else
		dp->dist_until_grid_side.x = ((dp->inspected_grid.x + 1) - start.x)
			* dp->rate_of_change.x;
	if (dir.y < 0)
		dp->dist_until_grid_side.y = (start.y - dp->inspected_grid.y)
			* dp->rate_of_change.y;
	else
		dp->dist_until_grid_side.y = ((dp->inspected_grid.y + 1) - start.y)
			* dp->rate_of_change.y;
	dp->found_cell = false;
	dp->max_distance = max_distance;
	dp->distance = 0;
}

static void	check_next_grid_cell(t_dda_params *dp)
{
	if (dp->dist_until_grid_side.x < dp->dist_until_grid_side.y)
	{
		dp->side = 0;
		dp->inspected_grid.x += dp->ray_step.x;
		dp->distance = dp->dist_until_grid_side.x;
		dp->dist_until_grid_side.x += dp->rate_of_change.x;
	}
	else
	{
		dp->side = 1;
		dp->inspected_grid.y += dp->ray_step.y;
		dp->distance = dp->dist_until_grid_side.y;
		dp->dist_until_grid_side.y += dp->rate_of_change.y;
	}
}
