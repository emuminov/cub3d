/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:51:03 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 16:42:01 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>

int	exit_game(t_game *g)
{
	mlx_destroy_image(g->mlx, g->frame.img);
	destroy_textures_array(g, g->wall_textures, 4);
	destroy_textures_array(g, g->idle_textures, IDLE_FRAMES);
	destroy_textures_array(g, g->idle_flower_textures, IDLE_FLOWER_FRAMES);
	destroy_textures_array(g, g->walk_textures, WALK_FRAMES);
	destroy_textures_array(g, g->walk_flower_textures, WALK_FLOWER_FRAMES);
	destroy_textures_array(g, g->flower_in_textures, FLOWER_IN_FRAMES);
	destroy_textures_array(g, g->flower_out_textures, FLOWER_OUT_FRAMES);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	free(g->len_tab);
	free_tab(g->map);
	exit(0);
}
