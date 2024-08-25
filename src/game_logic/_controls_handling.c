/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _controls_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:12:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 19:57:06 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/game_logic.h"
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>

int	exit_hook_cross(t_game *g)
{
	int	i;

	i = -1;
	mlx_destroy_image(g->mlx, g->frame.img);
	while (++i < 4)
		mlx_destroy_image(g->mlx, g->texture[i].img);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	free_config(&g->conf);
	free_tab(g->map);
	exit(0);
}

bool	is_move_key_pressed(t_game *g)
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
