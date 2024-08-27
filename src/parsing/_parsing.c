/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:31:55 by eandre            #+#    #+#             */
/*   Updated: 2024/08/27 16:42:52 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

void	pre_parsing(t_config_parsing *conf)
{
	char	*line;

	line = get_next_line(conf->map_fd);
	if (line == NULL)
	{
		printf("\033[0;31m""Error\nMap is empty!\n""\033[0m");
		close(conf->map_fd);
		exit (1);
	}
	while (parse_line(line, conf) == 1)
		line = get_next_line(conf->map_fd);
	free(line);
	close(conf->map_fd);
	if (conf->keys_finish == 0)
		return (printf("\033[0;31m"
				"Error\nThe map contains only keys!\n""\033[0m"), exit(1));
	if (conf->ceiling_c[0] > 255 || conf->ceiling_c[1] > 255
		|| conf->ceiling_c[2] > 255 || conf->floor_c[0] > 255
		|| conf->floor_c[1] > 255 || conf->floor_c[2] > 255)
		return (printf("\033[0;31m" \
			"Error\nOne of the number is above the char limit!\n""\033[0m")
			, exit(1));
}

int	map_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = -1;
	if ((!conf->paths[north_tex][0] || !conf->paths[south_tex][0]
			|| !conf->paths[west_tex][0] || !conf->paths[east_tex][0]
			|| conf->floor_c[0] == -1 || conf->ceiling_c[0] == -1)
		|| key_finish_check(gnl, conf))
		return (0);
	while (gnl[++i])
	{
		if (ft_strchr(" 01NESW\n", gnl[i]) == NULL)
			return (printf("\033[0;31m"
					"Error\nUnrecognized character in map!\n""\033[0m")
				, get_next_line(-1), free_config_p(conf), free(gnl)
				, exit(1), 0);
	}
	if (i == 1 && gnl[0] == '\n')
		return (printf("\033[0;31m"
				"Error\nA map line is empty!\n""\033[0m"), \
				get_next_line(-1), free_config_p(conf), free(gnl), exit(1), 0);
	conf->map_1d = ft_strjoin_free(conf->map_1d, gnl);
	if (conf->map_1d == NULL)
		return (get_next_line(-1), free_config_p(conf), free(gnl), exit(1), 0);
	return (1);
}

int	parse_line(char *line, t_config_parsing *conf_p)
{
	int	key_rv;

	key_rv = 0;
	if (line == NULL)
		return (0);
	if (conf_p->keys_finish == 0)
	{
		key_rv += north_key_manager(line, conf_p);
		key_rv += south_key_manager(line, conf_p);
		key_rv += east_key_manager(line, conf_p);
		key_rv += west_key_manager(line, conf_p);
		key_rv += floor_key_manager(line, conf_p);
		key_rv += ceiling_key_manager(line, conf_p);
	}
	conf_p->keys_finish += map_manager(line, conf_p);
	if (key_rv != 1 && (ft_strcmp(line, "\n") != 0) && conf_p->keys_finish == 0)
	{
		printf("\033[0;31m""Error\nUnrecognized character in keys!\n""\033[0m");
		get_next_line(-1);
		return (free_config_p(conf_p), free(line), exit(1), 0);
	}
	free(line);
	return (1);
}
