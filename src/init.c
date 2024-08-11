/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 01:23:57 by emuminov         ###   ########.fr       */
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
	conf.floor_c[0] = -1;
	conf.floor_c[1] = -1;
	conf.floor_c[2] = -1;
	conf.ceiling_c[0] = -1;
	conf.ceiling_c[1] = -1;
	conf.ceiling_c[2] = -1;
	conf.map_1d = NULL;
	conf.keys_finish = 0;
	conf.map_fd = -1;
	return (conf);
}

t_config	config_init(void)
{
	t_config	conf;

	conf.north_fd = -1;
	conf.east_fd = -1;
	conf.south_fd = -1;
	conf.west_fd = -1;
	conf.floor_c[0] = -1;
	conf.floor_c[1] = -1;
	conf.floor_c[2] = -1;
	conf.ceiling_c[0] = -1;
	conf.ceiling_c[1] = -1;
	conf.ceiling_c[2] = -1;
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
	if (parse_map(game.map_dup) == 1)
	{
		free_config_p(&conf_p);
		free_config(&game.conf);
		free_tab(game.map_dup);
		free_tab(game.map);
		exit (1);
	}
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

// void	manage_x_fill(char **tab, int *len_tab, t_coord cur, t_coord *stack)
// {

// }

// void	manage_y_fill(char **tab, int len_strs, t_coord cur, t_coord *stack)
// {

// }

int	cur_border_checker(t_coord cur, int *len_tab, int len_strs)
{
	return (cur.y == 0 || cur.y == len_strs - 1 || cur.x == 0
	|| cur.x == len_tab[cur.y] - 1 || (cur.y + 1 < len_strs
	&& cur.x >= len_tab[cur.y + 1]) || (cur.y > 0
	&& cur.x >= len_tab[cur.y - 1]));
}

int	fill(char **tab, int len_strs, t_coord cur, int *len_tab)
{
	int		stack_size;
	t_coord	*stack;
	int		inturn;

	if (cur_border_checker(cur, len_tab, len_strs) == 1)
		return (1);
	inturn = 0;
	stack = malloc(sizeof(t_coord) * len_strs * len_tab[0]);
	if (stack == NULL)
		return (printf("\033[0;31m""Error\nMalloc error!\n""\033[0m"), 2);
	stack_size = 0;
	stack[stack_size++] = cur;
	while (stack_size-- > 0)
	{
		cur = stack[stack_size];
		if (cur.y < 0 || cur.y >= len_strs || cur.x < 0 || cur.x
			>= len_tab[cur.y] || (tab[cur.y][cur.x] == '1'
			|| tab[cur.y][cur.x] == 'F'))
			continue ;
		tab[cur.y][cur.x] = 'F';
		inturn |= (cur.y == 0 || cur.y == len_strs - 1 || cur.x == 0
				|| cur.x == len_tab[cur.y] - 1);
		if ((cur.y + 1 < len_strs && cur.x >= len_tab[cur.y + 1])
			|| (cur.y - 1 < len_strs && cur.x >= len_tab[cur.y - 1]))
			inturn = 1;
		if (cur.x - 1 >= 0 && tab[cur.y][cur.x - 1] != '1'
				&& tab[cur.y][cur.x - 1] != 'F')
			stack[stack_size++] = (t_coord){cur.x - 1, cur.y};
		if (cur.x + 1 < len_tab[cur.y] && tab[cur.y][cur.x + 1] != '1'
				&& tab[cur.y][cur.x + 1] != 'F')
			stack[stack_size++] = (t_coord){cur.x + 1, cur.y};
		if (cur.y - 1 >= 0 && tab[cur.y - 1][cur.x] != '1'
				&& tab[cur.y - 1][cur.x] != 'F')
			stack[stack_size++] = (t_coord){cur.x, cur.y - 1};
		if (cur.y + 1 < len_strs && tab[cur.y + 1][cur.x] != '1'
				&& tab[cur.y + 1][cur.x] != 'F')
			stack[stack_size++] = (t_coord){cur.x, cur.y + 1};
	}
	return (free(stack), inturn);
}

//TODO while instead of recursive
// int	fill(char **tab, int len_strs, t_coord cur, int *len_tab)
// {
// 	int	inturn;

// 	inturn = (!(cur.y < 0 || cur.x < 0)
// 		&& ((cur.y == len_strs || cur.x == len_tab[cur.y] 
// 		|| cur.x == 0 || cur.y == 0) && (!tab[cur.y] 
// 		|| (tab[cur.y][cur.x] == '0' || tab[cur.y][cur.x] == ' ' 
// 		|| tab[cur.y][cur.x] == '\0'))));
// 	if (cur.y < 0 || cur.y >= len_strs || cur.x < 0 || cur.x >= len_tab[cur.y]
// 		|| (tab[cur.y][cur.x] == '1' || tab[cur.y][cur.x] == 'F'))
// 		return (inturn);
// 	tab[cur.y][cur.x] = 'F';
// 	inturn += fill(tab, len_strs, (t_coord){cur.x - 1, cur.y}, len_tab);
// 	inturn += fill(tab, len_strs, (t_coord){cur.x + 1, cur.y}, len_tab);
// 	inturn += fill(tab, len_strs, (t_coord){cur.x, cur.y - 1}, len_tab);
// 	inturn += fill(tab, len_strs, (t_coord){cur.x, cur.y + 1}, len_tab);
// 	return (inturn);
// }

int	get_max_and_fill(char **map, int *len_tab);

int	parse_map(char **map)
{
	int		*len_tab;
	int		i;
	t_coord	start;

	start = get_start(map);
	if (start.y == -1 && start.x == -1)
		return (printf("\033[0;31m""Error\nThe map needs to have one player!\n"
			"\033[0m"), 1);
	len_tab = malloc(sizeof(int) * ft_strslen(map));
	if (len_tab == NULL)
		return (printf("\033[0;31m""Error\nMalloc error!\n"
			"\033[0m"), 1);
	i = -1;
	while (map[++i])
		len_tab[i] = (int)ft_strlen(map[i]);
	i = fill(map, (int)ft_strslen(map), start, len_tab);
	if (i == 1)
	{
		printf("\033[0;31m""Error\nThe map is not closed!\n""\033[0m");
		return (free(len_tab), 1);
	}
	if (i == 2)
		return (free(len_tab), 1);
	return (free(len_tab), 0);
}

t_coord	get_start(char **map)
{
	t_coord	start;
	int		i;
	int		j;

	i = -1;
	start.x = -1;
	start.y = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && (start.y == -1 && start.x == -1))
			{
				start.y = i;
				start.x = j;
			}
			else if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && (start.y != -1 && start.x != -1))
				return ((t_coord){-1, -1});
		}
	}
	return (start);
}
