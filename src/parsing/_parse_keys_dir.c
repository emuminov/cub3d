/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_keys_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:10:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/26 14:20:55 by eandre           ###   ########.fr       */
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
	if (conf->paths[north_tex] != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	conf->paths[north_tex] = ft_strdup(&gnl[i]);
	if (conf->paths[north_tex] == NULL)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->paths[north_tex][ft_strlen(conf->paths[north_tex]) - 1] = '\0';
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
	if (conf->paths[east_tex] != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	conf->paths[east_tex] = ft_strdup(&gnl[i]);
	if (conf->paths[east_tex] == NULL)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->paths[east_tex][ft_strlen(conf->paths[east_tex]) - 1] = '\0';
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
	if (conf->paths[west_tex] != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	conf->paths[west_tex] = ft_strdup(&gnl[i]);
	if (conf->paths[west_tex] == NULL)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->paths[west_tex][ft_strlen(conf->paths[west_tex]) - 1] = '\0';
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
	if (conf->paths[south_tex] != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	i += 2;
	while (gnl[i] == ' ')
		i++;
	conf->paths[south_tex] = ft_strdup(&gnl[i]);
	if (conf->paths[south_tex] == NULL)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->paths[south_tex][ft_strlen(conf->paths[south_tex]) - 1] = '\0';
	return (1);
}
