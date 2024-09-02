/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_keys_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:12:17 by eandre            #+#    #+#             */
/*   Updated: 2024/09/02 18:26:29 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	parse_ceiling_key(char *line, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "C", 1) || check_errors_keys(&line[i], conf, 1, 1))
		return (0);
	if (conf->ceil_c[0] != -1)
		return (printf("\033[0;31m"
				"Error\nDouble keys are not allowed!\n""\033[0m")
			, get_next_line(-1), free(line), exit(1), 0);
	i += 1;
	while (line[i] == ' ')
		i++;
	if (ft_strchr(&line[i], ',') != NULL && ft_strrchr(line, ',') != NULL)
	{
		conf->ceil_c[0] = check_rgb(&line[i], line, conf);
		conf->ceil_c[1] = check_rgb(ft_strchr(&line[i], ',') + 1, line, conf);
		conf->ceil_c[2] = check_rgb(ft_strrchr(line, ',') + 1, line, conf);
	}
	if (charcmp(line, ',') != 2)
		return (printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m")
			, get_next_line(-1), free(line), exit(1), 0);
	return (1);
}

int	parse_floor_key(char *line, t_config_parsing *conf)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "F", 1) || check_errors_keys(&line[i], conf, 1, 1))
		return (0);
	if (conf->floor_c[0] != -1)
		return (printf("\033[0;31m"
				"Error\nDouble keys are not allowed!\n""\033[0m")
			, get_next_line(-1), free(line), exit(1), 0);
	i += 1;
	while (line[i] == ' ')
		i++;
	if (ft_strchr(&line[i], ',') != NULL && ft_strrchr(line, ',') != NULL)
	{
		conf->floor_c[0] = check_rgb(&line[i], line, conf);
		conf->floor_c[1] = check_rgb(ft_strchr(&line[i], ',') + 1, line, conf);
		conf->floor_c[2] = check_rgb(ft_strrchr(line, ',') + 1, line, conf);
	}
	if (charcmp(line, ',') != 2)
		return (printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m")
			, get_next_line(-1), free(line), exit(1), 0);
	return (1);
}
