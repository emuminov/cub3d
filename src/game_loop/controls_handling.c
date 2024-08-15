/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:12:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/21 18:17:16 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h>

int	exit_hook_cross(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	exit(0);
}

bool	is_any_key_pressed(t_game *g)
{
	return (g->controls.rotate_right_pressed || g->controls.rotate_left_pressed
		|| g->controls.move_left_pressed || g->controls.move_right_pressed
		|| g->controls.move_down_pressed || g->controls.move_up_pressed);
}

int	handle_key_press(int keysym, t_game *g)
{
	if (keysym == XK_Left)
		g->controls.rotate_left_pressed = true;
	else if (keysym == XK_Right)
		g->controls.rotate_right_pressed = true;
	else if (keysym == XK_w)
		g->controls.move_up_pressed = true;
	else if (keysym == XK_s)
		g->controls.move_down_pressed = true;
	else if (keysym == XK_a)
		g->controls.move_left_pressed = true;
	else if (keysym == XK_d)
		g->controls.move_right_pressed = true;
	else if (keysym == XK_e)
		toggle_door(g);
	else if (keysym == XK_Escape)
		exit_hook_cross(g);
	return (0);
}

int	handle_key_release(int keysym, t_game *g)
{
	if (keysym == XK_Left)
		g->controls.rotate_left_pressed = false;
	else if (keysym == XK_Right)
		g->controls.rotate_right_pressed = false;
	else if (keysym == XK_w)
		g->controls.move_up_pressed = false;
	else if (keysym == XK_s)
		g->controls.move_down_pressed = false;
	else if (keysym == XK_a)
		g->controls.move_left_pressed = false;
	else if (keysym == XK_d)
		g->controls.move_right_pressed = false;
	return (0);
}
