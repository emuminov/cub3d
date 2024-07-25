/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/07/26 00:38:46 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_config_parsing	config_parsing_init(void)
{
	t_config_parsing	conf;

	conf.north_path = NULL;
	conf.east_path = NULL;
	conf.west_path = NULL;
	conf.south_path = NULL;
	conf.floor_c = NULL;
	conf.map_1d = NULL;
	conf.keys_finished = 0;
	conf.map_fd = -1;
	conf.ceiling_c = NULL;
	return (conf);
}

t_config	config_init(void)
{
	t_config	conf;

	conf.north_fd = -1;
	conf.east_fd = -1;
	conf.south_fd = -1;
	conf.west_fd = -1;
	conf.floor_c = NULL;
	conf.ceiling_c = NULL;
	return (conf);
}

t_game	game_init(int argc, char **argv)
{
	int					fd;
	t_game				game;
	t_config_parsing	conf_p;

	fd = error_manager(argc, argv[1]);
	conf_p = config_parsing_init();
	game.conf = config_init();
	parse_map(fd, &conf_p, &game);
	paths_errors(&conf_p);
	open_paths(&conf_p, &game.conf);
	free_config_p(&conf_p);
	free_config(&game.conf);
	return (game);
}
