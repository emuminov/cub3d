/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:07:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/16 14:52:10 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_config_p(t_config_parsing *conf)
{
	// if (conf->north_path != NULL)
	// 	free(conf->north_path);
	// if (conf->east_path != NULL)
	// 	free(conf->east_path);
	// if (conf->south_path != NULL)
	// 	free(conf->south_path);
	// if (conf->west_path != NULL)
	// 	free(conf->west_path);
	if (conf->floor_c != NULL)
		free(conf->floor_c);
	if (conf->ceiling_c != NULL)
		free(conf->ceiling_c);
	if (conf->map_1d != NULL)
		free(conf->map_1d);
	if (conf->map_fd != -1)
		close(conf->map_fd);
}

void	free_config(t_config *conf)
{
	if (conf->floor_c != NULL)
		free(conf->floor_c);
	if (conf->ceiling_c != NULL)
		free(conf->ceiling_c);
	if (conf->north_path != NULL)
		free(conf->north_path);
	if (conf->east_path != NULL)
		free(conf->east_path);
	if (conf->south_path != NULL)
		free(conf->south_path);
	if (conf->west_path != NULL)
		free(conf->west_path);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
