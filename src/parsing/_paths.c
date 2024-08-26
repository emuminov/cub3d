/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _paths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:18:26 by eandre            #+#    #+#             */
/*   Updated: 2024/08/26 15:15:34 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

void	paths_errors(t_config_parsing *conf)
{
	int	i;

	if (!conf->paths[north_tex][0] || !conf->paths[south_tex][0]
		|| !conf->paths[west_tex][0] || !conf->paths[east_tex][0]
		|| conf->floor_c[0] == -1 || conf->ceiling_c[0] == -1)
	{
		printf("\033[0;31m""Error\nA key is missing!\n""\033[0m");
		free_config_p(conf);
		exit (1);
	}
	i = -1;
	while (++i < 4)
		path_format_checker(conf->paths[i], conf);
}

void	path_format_checker(char *str, t_config_parsing *conf)
{
	char	*check;

	check = ft_strnstr(str, ".xpm", ft_strlen(str));
	if (check == NULL || ft_strncmp(".xpm", check, 5) != 0)
	{
		printf("\033[0;31m"
			"Error\nOne of the textures is not in a .xpm format!\n""\033[0m");
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
