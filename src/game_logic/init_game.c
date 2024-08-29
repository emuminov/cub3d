/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:05:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/29 23:11:52 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_logic.h"
#include "../../include/constants.h"
#include "../minilibx-linux/mlx.h"
#include "../../include/cub3d.h"
#include "../libft/libft.h"
#include <X11/XKBlib.h>
#include <stdlib.h>
#include <stdio.h>

/* Contains functions that contain functions for initialization of graphics */

static int	game_loop(t_game *g);

int	create_window(t_game *g)
{
	if (init_img_data(g->mlx, &g->frame, g->window_size) == 1)
		return (1);
	g->win = mlx_new_window(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	if (g->win == NULL)
		return (1);
	return (0);
}

void	start_game_loop(t_game *g)
{
	mlx_mouse_get_pos(g->mlx, g->win, &g->old_mouse_pos.x, &g->old_mouse_pos.y);
	mlx_hook(g->win, 2, (1L << 0), handle_key_press, g);
	mlx_hook(g->win, 3, (1L << 1), handle_key_release, g);
	mlx_hook(g->win, 6, (1L << 6), handle_mouse, g);
	mlx_hook(g->win, DestroyNotify, StructureNotifyMask, exit_game, g);
	mlx_loop_hook(g->mlx, game_loop, g);
	mlx_loop(g->mlx);
}

void	init_textures(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		g->texture[i].img = mlx_xpm_file_to_image(g->mlx, g->conf.paths[i],
				&g->texture[i].dimensions.x, &g->texture[i].dimensions.y);
		if (g->texture[i].img == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(g->mlx, g->texture[i].img);
			mlx_destroy_display(g->mlx);
			free(g->mlx);
			free_tab(g->map);
			printf("\033[0;31m""Error\nA xpm file is not valid!\n""\033[0m");
			exit(1);
		}
		if (g->texture[i].dimensions.x > g->window_size.x
			|| g->texture[i].dimensions.y > g->window_size.y)
			resize_image(g, &g->texture[i], g->window_size.x, g->window_size.y);
		g->texture[i].addr = mlx_get_data_addr(g->texture[i].img,
				&g->texture[i].bits_per_pixel, &g->texture[i].line_len,
				&g->texture[i].endian);
	}
}

static void	init_animations_path(t_game *g)
{
	ft_strlcpy(g->idle_tex_path[0], "./textures/hand_anim/frame_0.xpm", 33);
	ft_strlcpy(g->idle_tex_path[1], "./textures/hand_anim/frame_1.xpm", 33);
	ft_strlcpy(g->idle_tex_path[2], "./textures/hand_anim/frame_2.xpm", 33);
	ft_strlcpy(g->idle_tex_path[3], "./textures/hand_anim/frame_3.xpm", 33);
	ft_strlcpy(g->idle_tex_path[4], "./textures/hand_anim/frame_4.xpm", 33);
	ft_strlcpy(g->idle_tex_path[5], "./textures/hand_anim/frame_5.xpm", 33);
	ft_strlcpy(g->walk_tex_path[0], "./textures/walk_anim/frame_0.xpm", 33);
	ft_strlcpy(g->walk_tex_path[1], "./textures/walk_anim/frame_1.xpm", 33);
	ft_strlcpy(g->walk_tex_path[2], "./textures/walk_anim/frame_2.xpm", 33);
	ft_strlcpy(g->walk_tex_path[3], "./textures/walk_anim/frame_3.xpm", 33);
	ft_strlcpy(g->walk_tex_path[4], "./textures/walk_anim/frame_4.xpm", 33);
	ft_strlcpy(g->walk_tex_path[5], "./textures/walk_anim/frame_5.xpm", 33);
	ft_strlcpy(g->walk_tex_path[6], "./textures/walk_anim/frame_6.xpm", 33);
	ft_strlcpy(g->walk_tex_path[7], "./textures/walk_anim/frame_7.xpm", 33);
}

static void	init_animations(t_game *g, t_img *texture, int max
, char (*path)[33])
{
	int	i;

	i = 0;
	while (i < max)
	{
		texture[i].img = mlx_xpm_file_to_image(g->mlx,
				path[i],
				&texture[i].dimensions.x,
				&texture[i].dimensions.y);
		resize_image(g, &texture[i],
			g->window_size.x, g->window_size.y);
		texture[i].addr = mlx_get_data_addr(texture[i].img,
				&texture[i].bits_per_pixel,
				&texture[i].line_len,
				&texture[i].endian);
		i++;
	}
}

/* Temprorary function that substitutes parsoing with hardcoded values */
// TODO: delete later, temporary function
int	_old_start_mlx(t_game *g, int x, int y)
{
	int	dummy_mouse_pos_y;

	(void)dummy_mouse_pos_y;
	g->window_size.x = x;
	g->window_size.y = y;
	g->mlx = mlx_init();
	init_textures(g);
	init_animations_path(g);
	init_animations(g, g->idle_textures, 6, g->idle_tex_path);
	init_animations(g, g->walk_textures, 8, g->walk_tex_path);
	g->win = mlx_new_window(g->mlx, x, y, "Cub3d");
	init_img_data(g->mlx, &g->frame, g->window_size);
	mlx_mouse_get_pos(g->mlx, g->win, &g->mouse_pos, &y);
	start_game_loop(g);
	return (0);
}

static int	game_loop(t_game *g)
{
	if (is_move_key_pressed(g))
	{
		resolve_rotation(g);
		resolve_movement(g);
	}
	render_3d_graphics(g);
	return (0);
}
