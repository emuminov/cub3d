/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_keys_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:10:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 16:51:28 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	north_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (gnl[i] == ' ')
		i++;
	if (ft_strncmp(&gnl[i], "NO", 2) || error_key(&gnl[i], conf, 2, 1) == 1)
		return (0);
	if (conf->north_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	conf->north_path = ft_strdup(&gnl[i]);
	if (conf->north_path == NULL)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->north_path[ft_strlen(conf->north_path) - 1] = '\0';
	return (1);
}

int	east_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (gnl[i] == ' ')
		i++;
	if (ft_strncmp(&gnl[i], "EA", 2) || error_key(&gnl[i], conf, 2, 1) == 1)
		return (0);
	if (conf->east_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	conf->east_path = ft_strdup(&gnl[i]);
	if (conf->east_path == NULL)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->east_path[ft_strlen(conf->east_path) - 1] = '\0';
	return (1);
}

int	west_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (gnl[i] == ' ')
		i++;
	if (ft_strncmp(&gnl[i], "WE", 2) || error_key(&gnl[i], conf, 2, 1) == 1)
		return (0);
	if (conf->west_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	conf->west_path = ft_strdup(&gnl[i]);
	if (conf->west_path == NULL)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->west_path[ft_strlen(conf->west_path) - 1] = '\0';
	return (1);
}

int	south_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (gnl[i] == ' ')
		i++;
	if (ft_strncmp(&gnl[i], "SO", 2) || error_key(&gnl[i], conf, 2, 1) == 1)
		return (0);
	if (conf->south_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	conf->south_path = ft_strdup(&gnl[i]);
	if (conf->south_path == NULL)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->south_path[ft_strlen(conf->south_path) - 1] = '\0';
	return (1);
}
