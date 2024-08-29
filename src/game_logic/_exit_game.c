/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:51:03 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/29 22:18:53 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>

int	exit_game(t_game *g)
{
	int	i;

	i = -1;
	mlx_destroy_image(g->mlx, g->frame.img);
	while (++i < 4)
		mlx_destroy_image(g->mlx, g->texture[i].img);
	i = -1;
	while (++i < 6)
		mlx_destroy_image(g->mlx, g->idle_textures[i].img);
	i = -1;
	while (++i < 8)
		mlx_destroy_image(g->mlx, g->walk_textures[i].img);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	free_tab(g->map);
	exit(0);
}
