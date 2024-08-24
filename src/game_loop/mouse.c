/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:54:48 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/24 17:49:47 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"

// TODO: replace hardcoded values
void	handle_mouse(t_game *g)
{
	int	x;
	int	y;

	(void)y;
	mlx_mouse_get_pos(g->mlx, g->win, &x, &y);
	if (x > g->old_mouse_pos)
		g->player.dir = vectorf_rotate(g->player.dir, 0.3);
	else if (x < g->old_mouse_pos)
		g->player.dir = vectorf_rotate(g->player.dir, -0.3);
	if (x < 210 || x > 430 || y < 210 || y > 430)
		mlx_mouse_move(g->mlx, g->win, 320, 320);
	// mlx_mouse_hide(g->mlx, g->win);
	g->old_mouse_pos = x;
}

