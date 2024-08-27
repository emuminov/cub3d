/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/08/27 16:34:29 by eandre           ###   ########.fr       */
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
		conf.ceiling_c[i] = -1;
	}
	conf.map_1d = NULL;
	conf.keys_finish = 0;
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

int	rgb_arr_to_int(int *rgb_arr)
{
	return (rgb_to_int(rgb_arr[0], rgb_arr[1], rgb_arr[2]));
}

void	config_init(t_game *g, t_config_parsing conf_p)
{
	int	i;
	int	j;

	g->conf.ceiling_c = rgb_arr_to_int(conf_p.ceiling_c);
	g->conf.floor_c = rgb_arr_to_int(conf_p.floor_c);
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

int	parse_cub_map(t_game *g, int argc, char **argv)
{
	int					fd;
	t_config_parsing	conf_p;
	char				**map_dup;

	fd = open_and_check_arg_errors(argc, argv[1]);
	conf_p = config_parsing_init(fd);
	pre_parsing(&conf_p);
	paths_errors(&conf_p);
	map_dup = ft_split(conf_p.map_1d, '\n');
	g->map = ft_split(conf_p.map_1d, '\n');
	if (g->map == NULL || map_dup == NULL
		|| parse_map(map_dup) == 1)
	{
		free_config_p(&conf_p);
		free_tab(map_dup);
		free_tab(g->map);
		exit (1);
	}
	config_init(g, conf_p);
	free_tab(map_dup);
	free_config_p(&conf_p);
	return (0);
}
