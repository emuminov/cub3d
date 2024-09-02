/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:07:17 by eandre            #+#    #+#             */
/*   Updated: 2024/09/02 18:38:46 by emuminov         ###   ########.fr       */
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

void	free_game(t_game *g)
{
	int	i;

	i = -1;
	free_tab(g->map);
	if (!g->mlx)
		return ;
	mlx_destroy_image(g->mlx, g->frame.img);
	while (++i < 4)
		mlx_destroy_image(g->mlx, g->wall_textures[i].img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
}

void	destroy_textures_array(t_game *g, t_img *textures, int size)
{
	int	i;
	i = 0;
	while (i < size && textures[i].img)
	{
		mlx_destroy_image(g->mlx, textures[i].img);
		i++;
	}
}
