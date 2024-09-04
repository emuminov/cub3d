/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mouse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:54:48 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/04 22:16:48 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/math_funcs.h"
#include "../minilibx-linux/mlx.h"

int	center_mouse_in_window(int x, int y, t_game *g)
{
	const t_pixel_point	center = vectori((WINDOW_WIDTH / 2),
			(WINDOW_HEIGHT / 2));

	if (x != center.x && y != center.y)
		mlx_mouse_move(g->mlx, g->win, center.x, center.y);
	return (0);
}

void	toggle_mouse(t_game *g)
{
	if (!g->mouse_enabled)
	{
		mlx_mouse_get_pos(g->mlx, g->win,
			&g->old_mouse_pos.x, &g->old_mouse_pos.y);
		g->mouse_enabled = true;
		mlx_mouse_move(g->mlx, g->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		if (SHOULD_HIDE_MOUSE)
			mlx_mouse_hide(g->mlx, g->win);
	}
	else
	{
		mlx_mouse_move(g->mlx, g->win, g->old_mouse_pos.x, g->old_mouse_pos.y);
		g->mouse_enabled = false;
		if (SHOULD_HIDE_MOUSE)
			mlx_mouse_show(g->mlx, g->win);
	}
}

int	handle_mouse(int x, int y, t_game *g)
{
	const t_pixel_point	center = vectori((WINDOW_WIDTH / 2),
			(WINDOW_HEIGHT / 2));
	int					delta;

	(void)y;
	if (!g->mouse_enabled)
		return (1);
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
	return (0);
}
