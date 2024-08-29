/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:31:55 by eandre            #+#    #+#             */
/*   Updated: 2024/08/29 23:12:03 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

void	parse(t_config_parsing *conf_p)
{
	char	*line;

	line = get_next_line(conf_p->map_fd);
	if (line == NULL)
	{
		printf("\033[0;31m""Error\nMap is empty!\n""\033[0m");
		close(conf_p->map_fd);
		exit (1);
	}
	while (parse_line(line, conf_p) == 1)
		line = get_next_line(conf_p->map_fd);
	free(line);
	close(conf_p->map_fd);
	if (conf_p->are_keys_validated == 0)
		return (printf("\033[0;31m"
				"Error\nThe map contains only keys!\n""\033[0m"), exit(1));
	if (conf_p->ceil_c[0] > 255 || conf_p->ceil_c[1] > 255
		|| conf_p->ceil_c[2] > 255 || conf_p->floor_c[0] > 255
		|| conf_p->floor_c[1] > 255 || conf_p->floor_c[2] > 255)
		return (printf("\033[0;31m" \
			"Error\nOne of the number is above the char limit!\n""\033[0m")
			, exit(1));
}

int	check_map_errors(char *line, t_config_parsing *conf_p)
{
	int	i;

	i = -1;
	if ((!conf_p->paths[north_tex][0] || !conf_p->paths[south_tex][0]
			|| !conf_p->paths[west_tex][0] || !conf_p->paths[east_tex][0]
			|| conf_p->floor_c[0] == -1 || conf_p->ceil_c[0] == -1)
		|| key_finish_check(line, conf_p))
		return (0);
	while (line[++i])
	{
		if (ft_strchr(" 01NESWD\n", line[i]) == NULL)
			return (printf("\033[0;31m"
					"Error\nUnrecognized character in map!\n""\033[0m")
				, get_next_line(-1), free_config_p(conf_p), free(line)
				, exit(1), 0);
	}
	if (i == 1 && line[0] == '\n')
		return (printf("\033[0;31m"
				"Error\nA map line is empty!\n""\033[0m"), \
			get_next_line(-1), free_config_p(conf_p), free(line), exit(1), 0);
	conf_p->map_1d = ft_strjoin_free(conf_p->map_1d, line);
	if (conf_p->map_1d == NULL)
		return (get_next_line(-1), free_config_p(conf_p), free(line), exit(1),
			0);
	return (1);
}

int	parse_line(char *line, t_config_parsing *conf_p)
{
	int	key_rv;

	key_rv = 0;
	if (line == NULL)
		return (0);
	if (conf_p->are_keys_validated == 0)
	{
		key_rv += parse_north_key(line, conf_p);
		key_rv += parse_south_key(line, conf_p);
		key_rv += parse_east_key(line, conf_p);
		key_rv += parse_west_key(line, conf_p);
		key_rv += parse_floor_key(line, conf_p);
		key_rv += parse_ceiling_key(line, conf_p);
	}
	conf_p->are_keys_validated += check_map_errors(line, conf_p);
	if (key_rv != 1 && (ft_strcmp(line, "\n") != 0)
		&& conf_p->are_keys_validated == 0)
	{
		printf("\033[0;31m""Error\nUnrecognized character in keys!\n""\033[0m");
		get_next_line(-1);
		return (free_config_p(conf_p), free(line), exit(1), 0);
	}
	free(line);
	return (1);
}
