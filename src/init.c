/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 00:50:03 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parsing.h"
#include <stdio.h>

t_config_parsing	config_parsing_init(void)
{
	t_config_parsing	conf;

	conf.north_path = NULL;
	conf.east_path = NULL;
	conf.west_path = NULL;
	conf.south_path = NULL;
	conf.floor_c = NULL;
	conf.map_1d = NULL;
	conf.keys_finish = 0;
	conf.map_fd = -1;
	conf.ceiling_c = NULL;
	return (conf);
}

t_config	config_init(void)
{
	t_config	conf;

	conf.north_path = NULL;
	conf.east_path = NULL;
	conf.west_path = NULL;
	conf.south_path = NULL;
	conf.floor_c = -1;
	conf.ceiling_c = -1;
	return (conf);
}

t_game	game_init(int argc, char **argv)
{
	int					fd;
	t_game				game;
	t_config_parsing	conf_p;


	// fd = error_manager(argc, argv[1]);
	// conf_p = config_parsing_init();
	// g.conf = config_init();
	// pre_parsing(fd, &conf_p);
	// paths_errors(&conf_p, &g.conf);


	fd = error_manager(argc, argv[1]);
	conf_p = config_parsing_init();
	game.conf = config_init();
	pre_parsing(fd, &conf_p);
	paths_errors(&conf_p, &game.conf);
	game.map = ft_split(conf_p.map_1d, '\n');
	parse_map(game.map);
	free_config_p(&conf_p);
	free_config(&game.conf);
	return (game);
}

size_t	ft_strslen(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	wall_checker(char **map, int i, int j)
{
	int	save;

	if (!map[i + 1] || !map[i - 1])
		return ;
	save = i;
	while (map[++save])
		if (map[save][j] == '0' || (map[save][j] != '1' && ((map[save][j + 1] && map[save][j + 1] == '0') || (map[save][j - 1] && map[save][j - 1] == '0'))))
			printf("wall error 3 WIP\n");
	while (map[--i] && i >= 0)
		if (map[i][j] == '0' || (map[i][j] != '1' && ((map[i][j + 1] && map[i][j + 1] == '0') || (map[i][j - 1] && map[i][j - 1] == '0'))))
			printf("wall error 4 WIP\n");
}

void	parse_map(char **map)
{
	int	i;
	int	j;
	int	len_strs;

	i = -1;
	len_strs = (int)ft_strslen(map);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			// if ((i == 0 || i == len_strs - 1) && (map[i][j] != ' ' && map[i][j] != '1'))
			// 	printf("wall error WIP\n");
			if ((map[i][j] == '0' && ((!map[i - 1] || !map[i - 1][j]) || (!map[i + 1] || !map[i + 1][j]))))
				printf("wall error WIP\n");
			if ((i != 0 && i != len_strs - 1) && (j == 0 || j == (int)(ft_strlen(map[i]) - 1)) && map[i][j] != ' ' && map[i][j] != '1')
				printf("wall error 2 WIP\n");
			if (map[i][j] == ' ')
				wall_checker(map, i, j);
		}
	}
}
