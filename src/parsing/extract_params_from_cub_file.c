/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_params_from_cub_file.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/08/29 23:01:43 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/parsing.h"
#include "../../include/math_funcs.h"
#include "../libft/libft.h"
#include <stdio.h>

void	free_config_p(t_config_parsing *conf)
{
	if (conf->map_1d != NULL)
		free(conf->map_1d);
	if (conf->map_fd != -1)
		close(conf->map_fd);
}

t_config_parsing	config_parsing_init(int fd)
{
	t_config_parsing	conf;
	int					i;

	i = -1;
	while (++i < 4)
		conf.paths[i][0] = '\0';
	i = -1;
	while (++i < 3)
	{
		conf.floor_c[i] = -1;
		conf.ceil_c[i] = -1;
	}
	conf.map_1d = NULL;
	conf.are_keys_validated = 0;
	conf.map_fd = fd;
	return (conf);
}

int	stack_stats_init(t_stack_stats *stack_stats, int len_strs
, int *len_tab, t_vectori cur)
{
	stack_stats->len_strs = len_strs;
	stack_stats->len_tab = len_tab;
	stack_stats->stack = malloc(sizeof(t_vectori) * len_strs * len_tab[0]);
	if (stack_stats->stack == NULL)
		return (1);
	stack_stats->stack_size = 0;
	stack_stats->stack[stack_stats->stack_size++] = cur;
	return (0);
}

void	config_init(t_game *g, t_config_parsing conf_p)
{
	int	i;
	int	j;

	g->conf.ceil_c = rgb_to_int(conf_p.ceil_c[0], conf_p.ceil_c[1],
			conf_p.ceil_c[2]);
	g->conf.floor_c = rgb_to_int(conf_p.floor_c[0], conf_p.floor_c[1],
			conf_p.floor_c[2]);
	i = -1;
	while (++i < 4)
		ft_strlcpy(g->conf.paths[i], conf_p.paths[i],
			ft_strlen(conf_p.paths[i]) + 1);
	i = -1;
	j = 0;
	while (g->map[++i])
		if ((int)ft_strlen(g->map[i]) > j)
			j = (int)ft_strlen(g->map[i]);
	g->conf.map_size = (t_grid_coordsi){.x = j, .y = i};
}

static void	set_initial_player_params(t_game *g)
{
	const t_grid_coordsi	start = get_start(g->map);

	if (g->map[start.y][start.x] == player_north)
	{
		g->player.dir = vectorf(0, -1);
		g->player.plane = vectorf(0.66, 0);
	}
	else if (g->map[start.y][start.x] == player_south)
	{
		g->player.dir = vectorf(0, 1);
		g->player.plane = vectorf(-0.66, 0);
	}
	else if (g->map[start.y][start.x] == player_east)
	{
		g->player.dir = vectorf(1, 0);
		g->player.plane = vectorf(0, 0.66);
	}
	else if (g->map[start.y][start.x] == player_west)
	{
		g->player.dir = vectorf(-1, 0);
		g->player.plane = vectorf(0, -0.66);
	}
	g->player.pos = vectorf(start.x + 0.5f, start.y + 0.5f);
}

int	extract_params_from_cub_file(t_game *g, int argc, char **argv)
{
	int					fd;
	t_config_parsing	conf_p;
	char				**map_dup;

	fd = open_and_check_arg_errors(argc, argv[1]);
	conf_p = config_parsing_init(fd);
	parse(&conf_p);
	validate_keys(&conf_p);
	g->map = ft_split(conf_p.map_1d, '\n');
	map_dup = ft_split(conf_p.map_1d, '\n');
	if (g->map == NULL || map_dup == NULL
		|| validate_map_walls(map_dup) == 1)
	{
		free_config_p(&conf_p);
		free_tab(map_dup);
		free_tab(g->map);
		exit (1);
	}
	config_init(g, conf_p);
	set_initial_player_params(g);
	free_tab(map_dup);
	free_config_p(&conf_p);
	return (0);
}
