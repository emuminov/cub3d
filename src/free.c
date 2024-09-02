/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:07:17 by eandre            #+#    #+#             */
/*   Updated: 2024/09/02 19:36:15 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "./minilibx-linux/mlx.h"
#include "../include/parsing.h"
#include <stdlib.h>
#include <unistd.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_config_p(t_config_parsing *conf)
{
	if (conf->map_1d != NULL)
		free(conf->map_1d);
	if (conf->map_fd != -1)
		close(conf->map_fd);
}

void	destroy_textures_array(t_game *g, t_img *textures, int size)
{
	int	i;

	i = 0;
	while (i < size && textures[i].img)
	{
		mlx_destroy_image(g->mlx, textures[i].img);
		textures[i].img = NULL;
		i++;
	}
}

void	free_game(t_game *g)
{
	free_tab(g->map);
	free(g->len_tab);
	if (!g->mlx)
		return ;
	if (g->frame.img)
		mlx_destroy_image(g->mlx, g->frame.img);
	destroy_textures_array(g, g->wall_textures, 4);
	destroy_textures_array(g, g->idle_textures, IDLE_FRAMES);
	destroy_textures_array(g, g->idle_flower_textures, IDLE_FLOWER_FRAMES);
	destroy_textures_array(g, g->walk_textures, WALK_FRAMES);
	destroy_textures_array(g, g->walk_flower_textures, WALK_FLOWER_FRAMES);
	destroy_textures_array(g, g->flower_in_textures, FLOWER_IN_FRAMES);
	destroy_textures_array(g, g->flower_out_textures, FLOWER_OUT_FRAMES);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
}
