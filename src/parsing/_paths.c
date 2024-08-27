/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _paths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:18:26 by eandre            #+#    #+#             */
/*   Updated: 2024/08/27 19:04:55 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

void	validate_keys(t_config_parsing *conf)
{
	int	i;

	if (!conf->paths[north_tex][0] || !conf->paths[south_tex][0]
		|| !conf->paths[west_tex][0] || !conf->paths[east_tex][0]
		|| conf->floor_c[0] == -1 || conf->ceil_c[0] == -1)
	{
		printf("\033[0;31m""Error\nA key is missing!\n""\033[0m");
		free_config_p(conf);
		exit (1);
	}
	i = -1;
	while (++i < 4)
		check_path_format(conf->paths[i], conf);
}

void	check_path_format(char *str, t_config_parsing *conf)
{
	char	*check;

	check = ft_strnstr(str, ".xpm", ft_strlen(str));
	if (check == NULL || ft_strncmp(".xpm", check, 5) != 0)
	{
		printf("\033[0;31m"
			"Error\nOne of the textures is not in a .xpm format!\n""\033[0m");
		free_config_p(conf);
		exit(1);
	}
}
