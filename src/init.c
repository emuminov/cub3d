/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 01:09:26 by emuminov         ###   ########.fr       */
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
	paths_errors(&conf_p);
	open_paths(&conf_p, &game.conf);
	game.map_dup = ft_split(conf_p.map_1d, '\n');
	game.map = ft_split(conf_p.map_1d, '\n');
	parse_map(game.map_dup);
	free_config_p(&conf_p);
	free_config(&game.conf);
	free_tab(game.map_dup);
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

//TODO while instead of recursive
int	fill(char **tab, t_coord size, t_coord cur, char tofind)
{
	int	inturn;

	inturn = ((cur.y == size.y || cur.x == size.x || cur.x == 0 || cur.y == 0) && (!tab[cur.y] || (tab[cur.y][cur.x] == tofind || tab[cur.y][cur.x] == ' ' || tab[cur.y][cur.x] == '\0')));
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| (tab[cur.y][cur.x] == '1' || tab[cur.y][cur.x] == 'F'))
		return (inturn);
	tab[cur.y][cur.x] = 'F';
	inturn += fill(tab, size, (t_coord){cur.x - 1, cur.y}, tofind);
	inturn += fill(tab, size, (t_coord){cur.x + 1, cur.y}, tofind);
	inturn += fill(tab, size, (t_coord){cur.x, cur.y - 1}, tofind);
	inturn += fill(tab, size, (t_coord){cur.x, cur.y + 1}, tofind);
	return (inturn);
}


void	parse_map(char **map)
{
	int		test;
	int		i;
	int		j;
	t_coord	start;

	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'W')
			{
				start.x = j;
				start.y = i;
				break ;
			}
			j++;
		}
		i++;
	}
	test = fill(map, (t_coord){ft_strslen(map), 10}, start, '0');
	if (test != 0)
		printf("wall error WIP\n");
}
