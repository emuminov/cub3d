/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:31:55 by eandre            #+#    #+#             */
/*   Updated: 2024/08/26 21:04:28 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

void	pre_parsing(int fd, t_config_parsing *conf)
{
	char	*gnl;

	gnl = get_next_line(fd);
	conf->map_fd = fd;
	if (gnl == NULL)
	{
		printf("\033[0;31m""Error\nMap is empty!\n""\033[0m");
		close(fd);
		exit (1);
	}
	while (parse_line(gnl, conf) == 1)
		gnl = get_next_line(fd);
	free(gnl);
	close(fd);
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

int	parse_line(char *gnl, t_config_parsing *conf_p)
{
	int	key_rv;

	key_rv = 0;
	if (gnl == NULL)
		return (0);
	if (conf_p->keys_finish == 0)
	{
		key_rv += north_key_manager(gnl, conf_p);
		key_rv += south_key_manager(gnl, conf_p);
		key_rv += east_key_manager(gnl, conf_p);
		key_rv += west_key_manager(gnl, conf_p);
		key_rv += floor_key_manager(gnl, conf_p);
		key_rv += ceiling_key_manager(gnl, conf_p);
	}
	conf_p->keys_finish += map_manager(gnl, conf_p);
	if (key_rv != 1 && (ft_strcmp(gnl, "\n") != 0) && conf_p->keys_finish == 0)
	{
		printf("\033[0;31m""Error\nUnrecognized character in keys!\n""\033[0m");
		get_next_line(-1);
		return (free_config_p(conf_p), free(gnl), exit(1), 0);
	}
	free(gnl);
	return (1);
}
