/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_keys_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:12:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 01:21:12 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/parsing.h"
#include <stdio.h>

//TODO: NEED TO FIX PRE KEY SPACES
int	ceiling_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (gnl[i] == ' ')
		i++;
	if (ft_strncmp(&gnl[i], "C", 1) != 0 || error_key(&gnl[i], conf, 1, 1) == 1)
		return (0);
	if (conf->ceiling_c[0] != -1)
		return (printf("\033[0;31m"
				"Error\nDouble keys are not allowed!\n""\033[0m")
			, get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	i += 1;
	while (gnl[i] == ' ')
		i++;
	if (ft_strchr(&gnl[i], ',') != NULL && ft_strrchr(gnl, ',') != NULL)
	{
		conf->ceiling_c[0] = ft_atoc(&gnl[i], gnl, conf);
		conf->ceiling_c[1] = ft_atoc(ft_strchr(&gnl[i], ',') + 1, gnl, conf);
		conf->ceiling_c[2] = ft_atoc(ft_strrchr(gnl, ',') + 1, gnl, conf);
	}
	if (charcmp(gnl, ',') != 2)
		return (printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m")
			, get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	return (1);
}

int	floor_key_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (gnl[i] == ' ')
		i++;
	if (ft_strncmp(&gnl[i], "F", 1) != 0 || error_key(&gnl[i], conf, 1, 1) == 1)
		return (0);
	if (conf->floor_c[0] != -1)
		return (printf("\033[0;31m"
				"Error\nDouble keys are not allowed!\n""\033[0m")
			, get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	i += 1;
	while (gnl[i] == ' ')
		i++;
	if (ft_strchr(&gnl[i], ',') != NULL && ft_strrchr(gnl, ',') != NULL)
	{
		conf->floor_c[0] = ft_atoc(&gnl[i], gnl, conf);
		conf->floor_c[1] = ft_atoc(ft_strchr(&gnl[i], ',') + 1, gnl, conf);
		conf->floor_c[2] = ft_atoc(ft_strrchr(gnl, ',') + 1, gnl, conf);
	}
	if (charcmp(gnl, ',') != 2)
		return (printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m")
			, get_next_line(-1), free(gnl), free_config_p(conf), exit(1), 0);
	return (1);
}
