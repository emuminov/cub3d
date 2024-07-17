/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/07/17 20:03:11 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_config	config_init(void)
{
	t_config	config;

	config.north_path = NULL;
	config.east_path = NULL;
	config.west_path = NULL;
	config.south_path = NULL;
	config.floor_color = NULL;
	config.ceiling_color = NULL;
	return (config);
}

t_game	game_init(int argc, char **argv)
{
	int		fd;
	t_game	game;

	fd = error_manager(argc, argv[1]);
	game.config = config_init();
	parse_map(fd, &game.config);
	return (game);
}
