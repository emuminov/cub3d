/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mouse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:54:48 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/28 16:05:43 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/math_funcs.h"
#include "../minilibx-linux/mlx.h"

void	toggle_mouse(t_game *g)
{
	if (!g->mouse_enabled)
	{
		mlx_mouse_get_pos(g->mlx, g->win,
			&g->old_mouse_pos.x, &g->old_mouse_pos.y);
		g->mouse_enabled = true;
		mlx_mouse_hide(g->mlx, g->win);
		mlx_mouse_move(g->mlx, g->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	else
	{
		mlx_mouse_show(g->mlx, g->win);
		mlx_mouse_move(g->mlx, g->win, g->old_mouse_pos.x, g->old_mouse_pos.y);
		g->mouse_enabled = false;
	}
}

int	handle_mouse(int x, int y, t_game *g)
{
	const t_pixel_point	center = vectori((WINDOW_WIDTH / 2),
			(WINDOW_HEIGHT / 2));
	int					delta;

	if (!g->mouse_enabled)
		return (1);
	(void)y;
	delta = x - center.x;
	if (delta > 0)
	{
		g->player.dir = vectorf_rotate(g->player.dir, MOUSE_ROTATION_SPEED);
		g->player.plane = vectorf_rotate(g->player.plane, MOUSE_ROTATION_SPEED);
	}
	else if (delta < 0)
	{
		g->player.dir = vectorf_rotate(g->player.dir, -MOUSE_ROTATION_SPEED);
		g->player.plane = vectorf_rotate(g->player.plane,
				-MOUSE_ROTATION_SPEED);
	}
	mlx_mouse_move(g->mlx, g->win, center.x, center.y);
	return (0);
}
