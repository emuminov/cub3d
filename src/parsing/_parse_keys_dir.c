/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_keys_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:10:17 by eandre            #+#    #+#             */
/*   Updated: 2024/08/27 19:14:51 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	parse_north_key(char *line, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "NO", 2)
		|| check_errors_keys(&line[i], conf, 2, 1))
		return (0);
	if (conf->paths[north_tex][0] != '\0')
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(line), exit(1), 0);
	}
	i += 2;
	while (line[i] == ' ')
		i++;
	ft_strlcpy(conf->paths[north_tex], &line[i], ft_strlen(&line[i]));
	return (1);
}

int	parse_east_key(char *line, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "EA", 2)
		|| check_errors_keys(&line[i], conf, 2, 1))
		return (0);
	if (conf->paths[east_tex][0] != '\0')
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(line), exit(1), 0);
	}
	i += 2;
	while (line[i] == ' ')
		i++;
	ft_strlcpy(conf->paths[east_tex], &line[i], ft_strlen(&line[i]));
	return (1);
}

int	parse_west_key(char *line, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "WE", 2)
		|| check_errors_keys(&line[i], conf, 2, 1))
		return (0);
	if (conf->paths[west_tex][0] != '\0')
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(line), exit(1), 0);
	}
	i += 2;
	while (line[i] == ' ')
		i++;
	ft_strlcpy(conf->paths[west_tex], &line[i], ft_strlen(&line[i]));
	return (1);
}

int	parse_south_key(char *line, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "SO", 2)
		|| check_errors_keys(&line[i], conf, 2, 1))
		return (0);
	if (conf->paths[south_tex][0] != '\0')
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(line), exit(1), 0);
	}
	i += 2;
	while (line[i] == ' ')
		i++;
	ft_strlcpy(conf->paths[south_tex], &line[i], ft_strlen(&line[i]));
	return (1);
}
