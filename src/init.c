/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/07/18 15:55:25 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_config	config_init(void)
{
	t_config	conf;

	conf.north_path = NULL;
	conf.east_path = NULL;
	conf.west_path = NULL;
	conf.south_path = NULL;
	conf.floor_c = NULL;
	conf.ceiling_c = NULL;
	return (conf);
}

t_game	game_init(int argc, char **argv)
{
	int		fd;
	t_game	game;

	fd = error_manager(argc, argv[1]);
	game.conf = config_init();
	parse_map(fd, &game.conf);
	return (game);
}
