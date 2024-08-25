/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:07:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 16:52:06 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>
#include <unistd.h>

void	free_config(t_config *conf)
{
	if (conf->east_fd != -1)
		close(conf->east_fd);
	if (conf->west_fd != -1)
		close(conf->west_fd);
	if (conf->north_fd != -1)
		close(conf->north_fd);
	if (conf->south_fd != -1)
		close(conf->south_fd);
}

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
