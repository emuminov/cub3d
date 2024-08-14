/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:12:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 16:02:13 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h>

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

t_vectorf	mouse_pos_to_grid_coordsf(t_game *g)
{
	int				x;
	int				y;
	t_grid_coordsf	mouse_grid_pos;

	mlx_mouse_get_pos(g->mlx, g->win, &x, &y);
	mouse_grid_pos = pixel_point_to_grid_coordsf((t_pixel_point){.x = x,
			.y = y});
	if (mouse_grid_pos.x > g->window_size.x)
		mouse_grid_pos.x = g->window_size.x;
	else if (mouse_grid_pos.x < 0)
		mouse_grid_pos.x = 0;
	if (mouse_grid_pos.y > g->window_size.y)
		mouse_grid_pos.y = g->window_size.y;
	else if (mouse_grid_pos.y < 0)
		mouse_grid_pos.y = 0;
	return mouse_grid_pos;
}
