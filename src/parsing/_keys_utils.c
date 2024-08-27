/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _keys_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:28:00 by eandre            #+#    #+#             */
/*   Updated: 2024/08/27 19:04:36 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	check_errors_keys(char *line, t_config_parsing *conf_p, int i,
		int strcmp_value)
{
	if (line[i] != '\0' && line[i] != '\n' && ft_isspace(line[i]) == 0)
		return (1);
	else if (line[i] == '\0' || line[i] == '\n')
		printf("\033[0;31m"
			"Error\nOne of the value of a key is empty!\n""\033[0m");
	else
	{
		while (line[i] == ' ')
			i++;
		if (ft_isspace(line[i]) == 1 && line[i] != '\n')
			printf("\033[0;31m"
				"Error\nOnly spaces are accepted\n""\033[0m");
		else if (line[i] == '\n' || line[i] == '\0')
			printf("\033[0;31m"
				"Error\nOne of the value of a key is empty!\n""\033[0m");
		else if (strcmp_value == 1)
			return (0);
	}
	get_next_line(-1);
	return (free(line), free_config_p(conf_p), exit(1), 1);
}

int	key_finish_check(char *line, t_config_parsing *conf)
{
	if (((ft_strncmp(line, "SO", 2) == 0 \
		&& (line[2] == '\0' || line[2] == '\n' || line[2] == ' ')) \
		|| (ft_strncmp(line, "NO", 2) == 0 \
		&& (line[2] == '\0' || line[2] == '\n' || line[2] == ' ')) \
		|| (ft_strncmp(line, "EA", 2) == 0 \
		&& (line[2] == '\0' || line[2] == '\n' || line[2] == ' ')) \
		|| (ft_strncmp(line, "WE", 2) == 0 \
		&& (line[2] == '\0' || line[2] == '\n' || line[2] == ' ')) \
		|| (ft_strncmp(line, "C", 1) == 0 \
		&& (line[1] == '\0' || line[1] == '\n' || line[1] == ' ')) \
		|| (ft_strncmp(line, "F", 1) == 0 \
		&& (line[1] == '\0' || line[1] == '\n' || line[1] == ' ')) \
		|| ft_strcmp(line, "\n") == 0) \
		&& conf->are_keys_validated == 0)
		return (1);
	return (0);
}
