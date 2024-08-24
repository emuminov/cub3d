/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:10:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 00:43:16 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/parsing.h"
#include <stdio.h>

int	north_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 2;
	if (ft_strncmp(gnl, "NO", 2) != 0 || error_key(gnl, conf, 2, 1) == 1)
		return (0);
	if (conf->north_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	while (gnl[i] == ' ')
		i++;
	conf->north_path = ft_strdup(&gnl[i]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->north_path[ft_strlen(conf->north_path) - 1] = '\0';
	return (1);
}

int	east_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 2;
	if (ft_strncmp(gnl, "EA", 2) != 0 || error_key(gnl, conf, 2, 1) == 1)
		return (0);
	if (conf->east_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	while (gnl[i] == ' ')
		i++;
	conf->east_path = ft_strdup(&gnl[i]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->east_path[ft_strlen(conf->east_path) - 1] = '\0';
	return (1);
}

int	west_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 2;
	if (ft_strncmp(gnl, "WE", 2) != 0 || error_key(gnl, conf, 2, 1) == 1)
		return (0);
	if (conf->west_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	while (gnl[i] == ' ')
		i++;
	conf->west_path = ft_strdup(&gnl[i]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->west_path[ft_strlen(conf->west_path) - 1] = '\0';
	return (1);
}

int	south_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 2;
	if (ft_strncmp(gnl, "SO", 2) != 0 || error_key(gnl, conf, 2, 1) == 1)
		return (0);
	if (conf->south_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	while (gnl[i] == ' ')
		i++;
	conf->south_path = ft_strdup(&gnl[i]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->south_path[ft_strlen(conf->south_path) - 1] = '\0';
	return (1);
}
