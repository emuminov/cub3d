/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_keys_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:10:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/26 21:03:54 by eandre           ###   ########.fr       */
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
	if (conf->paths[north_tex][0] != '\0')
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	ft_strlcpy(conf->paths[north_tex], &gnl[i], ft_strlen(&gnl[i]));
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
	if (conf->paths[east_tex][0] != '\0')
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	ft_strlcpy(conf->paths[east_tex], &gnl[i], ft_strlen(&gnl[i]));
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
	if (conf->paths[west_tex][0] != '\0')
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	ft_strlcpy(conf->paths[west_tex], &gnl[i], ft_strlen(&gnl[i]));
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
	if (conf->paths[south_tex][0] != '\0')
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	ft_strlcpy(conf->paths[south_tex], &gnl[i], ft_strlen(&gnl[i]));
	return (1);
}
