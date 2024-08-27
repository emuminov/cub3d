/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _keys_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:28:00 by eandre            #+#    #+#             */
/*   Updated: 2024/08/27 17:28:07 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	error_key(char *gnl, t_config_parsing *conf, int i, int strcmp_value)
{
	if (gnl[i] != '\0' && gnl[i] != '\n' && ft_isspace(gnl[i]) == 0)
		return (1);
	else if (gnl[i] == '\0' || gnl[i] == '\n')
		printf("\033[0;31m"
			"Error\nOne of the value of a key is empty!\n""\033[0m");
	else
	{
		while (gnl[i] == ' ')
			i++;
		if (ft_isspace(gnl[i]) == 1 && gnl[i] != '\n')
			printf("\033[0;31m"
				"Error\nOnly spaces are accepted\n""\033[0m");
		else if (gnl[i] == '\n' || gnl[i] == '\0')
			printf("\033[0;31m"
				"Error\nOne of the value of a key is empty!\n""\033[0m");
		else if (strcmp_value == 1)
			return (0);
	}
	get_next_line(-1);
	return (free(gnl), free_config_p(conf), exit(1), 1);
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
