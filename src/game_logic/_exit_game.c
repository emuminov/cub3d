/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:51:03 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/26 15:51:52 by emuminov         ###   ########.fr       */
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
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	free_config(&g->conf);
	free_tab(g->map);
	exit(0);
}
