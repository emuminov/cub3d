/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:07:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/28 22:52:55 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "./minilibx-linux/mlx.h"
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

void	free_game(t_game *g)
{
	int	i;

	i = -1;
	free_tab(g->map);
	mlx_destroy_image(g->mlx, g->frame.img);
	while (++i < 4)
		mlx_destroy_image(g->mlx, g->texture[i].img);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
}
