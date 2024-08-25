/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:45 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 18:42:18 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/parsing.h"
#include "../../include/math_funcs.h"
#include "../libft/libft.h"
#include <stdio.h>

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
	if (conf->map_1d != NULL)
		free(conf->map_1d);
	if (conf->map_fd != -1)
		close(conf->map_fd);
}

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

	// conf.paths = NULL;
	// conf.east_path = NULL;
	// conf.south_path = NULL;
	// conf.west_path = NULL;
	conf.floor_c = -1;
	conf.ceiling_c = -1;
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

int	parse_cub_map(t_game *g, int argc, char **argv)
{
	int					fd;
	t_config_parsing	conf_p;

	fd = error_manager(argc, argv[1]);
	conf_p = config_parsing_init();
	g->conf = config_init();
	pre_parsing(fd, &conf_p);
	paths_errors(&conf_p);
	// open_paths(&conf_p, &g->conf);
	g->map_dup = ft_split(conf_p.map_1d, '\n');
	g->map = ft_split(conf_p.map_1d, '\n');
	g->conf.ceiling_c = rgb_arr_to_int(conf_p.ceiling_c);
	g->conf.floor_c = rgb_arr_to_int(conf_p.floor_c);
	g->conf.paths[north_tex] = conf_p.north_path;
	g->conf.paths[south_tex] = conf_p.south_path;
	g->conf.paths[west_tex] = conf_p.west_path;
	g->conf.paths[east_tex] = conf_p.east_path;
	if (g->map == NULL || g->map_dup == NULL
		|| parse_map(g->map_dup) == 1)
	{
		free_config_p(&conf_p);
		free_config(&g->conf);
		free_tab(g->map_dup);
		free_tab(g->map);
		exit (1);
	}
	free_tab(g->map_dup);
	int	i = 0;
	int	j = 0;
	while (g->map[i])
	{
		if ((int)ft_strlen(g->map[i]) > j)
			j = (int)ft_strlen(g->map[i]);
		i++;
	}
	g->map_size = (t_grid_coordsi){.x = j, .y = i};
	free_config_p(&conf_p);
	return (0);
}
