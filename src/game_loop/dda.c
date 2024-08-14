/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:01 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 16:48:01 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* DDA algorithm for finding the nearest wall in the certain directions */

static void	set_initial_dda_params(t_dda_params *dp, t_grid_coordsf start,
		t_vectorf dir, double max_distance);
static void	check_next_grid_cell(t_dda_params *dp);

t_vectorf	check_wall_in_dir(t_game *g, t_dda_params *dp, t_grid_coordsf start,
		t_vectorf dir, double max_distance)
{
	t_vectorf	intersection;

	set_initial_dda_params(dp, start, dir, max_distance);
	while (!dp->found_wall && dp->distance < dp->max_distance)
	{
		check_next_grid_cell(dp);
		if (is_in_bounds_of_grid(dp->inspected_grid, g->map_size))
		{
			if (g->map[(int)dp->inspected_grid.y][(int)dp->inspected_grid.x] == '1')
				dp->found_wall = true;
		}
		else
			break ;
	}
	if (dp->found_wall)
		intersection = vectorf_add(start, vectorf_scale(dir, dp->distance));
	else
		intersection = (t_grid_coordsf){.x = -1, .y = -1};
	return intersection;
}

static void	set_initial_dda_params(t_dda_params *dp, t_grid_coordsf start,
		t_vectorf dir, double max_distance)
{
	dp->rate_of_change.x = abs_f(1 / dir.x);
	dp->rate_of_change.y = abs_f(1 / dir.y);
	dp->inspected_grid = (t_grid_coordsi){.x = (int)start.x, .y = start.y};
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
	dp->found_wall = false;
	dp->max_distance = max_distance;
	dp->distance = 0;
}

static void	check_next_grid_cell(t_dda_params *dp)
{
	if (dp->dist_until_grid_side.x < dp->dist_until_grid_side.y)
	{
		dp->inspected_grid.x += dp->ray_step.x;
		dp->distance = dp->dist_until_grid_side.x;
		dp->dist_until_grid_side.x += dp->rate_of_change.x;
	}
	else
	{
		dp->inspected_grid.y += dp->ray_step.y;
		dp->distance = dp->dist_until_grid_side.y;
		dp->dist_until_grid_side.y += dp->rate_of_change.y;
	}
}
