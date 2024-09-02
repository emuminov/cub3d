/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:05:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 14:33:10 by emuminov         ###   ########.fr       */
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
			free(g->len_tab);
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



void	init_animations_path(t_game *g)
{
	ft_strlcpy(g->idle_tex_path[0], IDLE_0, sizeof(IDLE_0));
	ft_strlcpy(g->idle_tex_path[1], IDLE_1, sizeof(IDLE_0));
	ft_strlcpy(g->idle_tex_path[2], IDLE_2, sizeof(IDLE_0));
	ft_strlcpy(g->idle_tex_path[3], IDLE_3, sizeof(IDLE_0));
	ft_strlcpy(g->idle_tex_path[4], IDLE_4, sizeof(IDLE_0));
	ft_strlcpy(g->idle_tex_path[5], IDLE_5, sizeof(IDLE_0));

	ft_strlcpy(g->walk_tex_path[0], WALK_0, sizeof(WALK_0));
	ft_strlcpy(g->walk_tex_path[1], WALK_1, sizeof(WALK_0));
	ft_strlcpy(g->walk_tex_path[2], WALK_2, sizeof(WALK_0));
	ft_strlcpy(g->walk_tex_path[3], WALK_3, sizeof(WALK_0));
	ft_strlcpy(g->walk_tex_path[4], WALK_4, sizeof(WALK_0));
	ft_strlcpy(g->walk_tex_path[5], WALK_5, sizeof(WALK_0));
	ft_strlcpy(g->walk_tex_path[6], WALK_6, sizeof(WALK_0));
	ft_strlcpy(g->walk_tex_path[7], WALK_7, sizeof(WALK_0));

	ft_strlcpy(g->idle_flower_tex_path[0], IDLE_FLOWER_0, sizeof(IDLE_FLOWER_0));
	ft_strlcpy(g->idle_flower_tex_path[1], IDLE_FLOWER_1, sizeof(IDLE_FLOWER_0));
	ft_strlcpy(g->idle_flower_tex_path[2], IDLE_FLOWER_2, sizeof(IDLE_FLOWER_0));
	ft_strlcpy(g->idle_flower_tex_path[3], IDLE_FLOWER_3, sizeof(IDLE_FLOWER_0));
	ft_strlcpy(g->idle_flower_tex_path[4], IDLE_FLOWER_4, sizeof(IDLE_FLOWER_0));
	ft_strlcpy(g->idle_flower_tex_path[5], IDLE_FLOWER_5, sizeof(IDLE_FLOWER_0));

	ft_strlcpy(g->walk_flower_tex_path[0], WALK_FLOWER_0, sizeof(WALK_FLOWER_0));
	ft_strlcpy(g->walk_flower_tex_path[1], WALK_FLOWER_1, sizeof(WALK_FLOWER_0));
	ft_strlcpy(g->walk_flower_tex_path[2], WALK_FLOWER_2, sizeof(WALK_FLOWER_0));
	ft_strlcpy(g->walk_flower_tex_path[3], WALK_FLOWER_3, sizeof(WALK_FLOWER_0));
	ft_strlcpy(g->walk_flower_tex_path[4], WALK_FLOWER_4, sizeof(WALK_FLOWER_0));
	ft_strlcpy(g->walk_flower_tex_path[5], WALK_FLOWER_5, sizeof(WALK_FLOWER_0));
	ft_strlcpy(g->walk_flower_tex_path[6], WALK_FLOWER_6, sizeof(WALK_FLOWER_0));
	ft_strlcpy(g->walk_flower_tex_path[7], WALK_FLOWER_7, sizeof(WALK_FLOWER_0));

	ft_strlcpy(g->flower_out_tex_path[0], FLOWER_OUT_00, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[1], FLOWER_OUT_01, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[2], FLOWER_OUT_02, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[3], FLOWER_OUT_03, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[4], FLOWER_OUT_04, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[5], FLOWER_OUT_05, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[6], FLOWER_OUT_06, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[7], FLOWER_OUT_07, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[8], FLOWER_OUT_08, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[9], FLOWER_OUT_09, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[10], FLOWER_OUT_10, sizeof(FLOWER_OUT_00));
	ft_strlcpy(g->flower_out_tex_path[11], FLOWER_OUT_11, sizeof(FLOWER_OUT_00));

	// g->flower_in_textures[0] =  mlx_xpm_file_to_image(g->mlx, FLOWER_IN_00, &g->flower_in_textures[0].dimensions.x, &g->flower_in_textures[0].dimensions.y);
	// g->flower_in_textures[1] =  FLOWER_IN_01, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[2] =  FLOWER_IN_02, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[3] =  FLOWER_IN_03, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[4] =  FLOWER_IN_04, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[5] =  FLOWER_IN_05, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[6] =  FLOWER_IN_06, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[7] =  FLOWER_IN_07, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[8] =  FLOWER_IN_08, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[9] =  FLOWER_IN_09, sizeof(FLOWER_IN_00));
	// g->flower_in_textures[10] = FLOWER_IN_10, sizeof(FLOWER_IN_00));
}

int	init_texture(t_game *g, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(g->mlx,
			path,
			&texture->dimensions.x,
			&texture->dimensions.y);
	if (texture->img == NULL)
		return (1);
	if (resize_image(g, texture, g->window_size.x, g->window_size.y) == 1)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_len,
			&texture->endian);
	return (0);
}

void	init_animations(t_game *g, t_img *texture, int max
, char **path)
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
