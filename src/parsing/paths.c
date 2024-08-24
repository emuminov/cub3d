/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:18:26 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 00:43:20 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/parsing.h"
#include <stdio.h>

void	paths_errors(t_config_parsing *conf_p, t_config *conf)
{
	if (!conf_p->east_path || !conf_p->north_path || !conf_p->south_path
		|| !conf_p->west_path || !conf_p->floor_c || !conf_p->ceiling_c)
	{
		printf("\033[0;31m""Error\nA key is missing!\n""\033[0m");
		free_config_p(conf_p);
		exit (1);
	}
	path_format_checker(conf_p->east_path, conf_p);
	path_format_checker(conf_p->north_path, conf_p);
	path_format_checker(conf_p->south_path, conf_p);
	path_format_checker(conf_p->west_path, conf_p);
	conf->east_path = conf_p->east_path;
	conf->north_path = conf_p->north_path;
	conf->south_path = conf_p->south_path;
	conf->west_path = conf_p->west_path;
}

void	path_format_checker(char *str, t_config_parsing *conf)
{
	char	*check;

	check = ft_strnstr(str, ".xpm", ft_strlen(str));
	if (check == NULL || ft_strncmp(".xpm", check, 5) != 0)
	{
		printf("\033[0;31m"
			"Error \nOne of the textures is not in a .xpm format!\n""\033[0m");
		free_config_p(conf);
		exit(1);
	}
}

// void	open_paths(t_config_parsing *conf_p, t_config *conf)
// {
// 	conf->east_fd = open(conf_p->east_path, O_RDONLY);
// 	if (conf->east_fd == -1)
// 		open_error_manager(conf_p, conf, conf_p->east_path, "East");
// 	conf->north_fd = open(conf_p->north_path, O_RDONLY);
// 	if (conf->north_fd == -1)
// 		open_error_manager(conf_p, conf, conf_p->north_path, "North");
// 	conf->west_fd = open(conf_p->west_path, O_RDONLY);
// 	if (conf->west_fd == -1)
// 		open_error_manager(conf_p, conf, conf_p->west_path, "West");
// 	conf->south_fd = open(conf_p->south_path, O_RDONLY);
// 	if (conf->south_fd == -1)
// 		open_error_manager(conf_p, conf, conf_p->south_path, "South");
// }

// void	open_error_manager(t_config_parsing *conf_p, t_config *conf,
// char *path, char *name)
// {
// 	printf("\033[0;31m"
// 		"Error\n%s path: %s: no such file or directory!\n""\033[0m", name,
// 		path);
// 	free_config_p(conf_p);
// 	free_config(conf);
// 	exit(1);
// }
