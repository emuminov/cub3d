/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:19:59 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 00:42:50 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

int	error_manager(int argc, char *argv)
{
	char	*check;
	int		fd;

	if (argc != 2)
	{
		printf("\033[0;31m""Error\nWrong number of arguments !\n""\033[0m");
		exit(1);
	}
	check = ft_strnstr(argv, ".cub", ft_strlen(argv));
	if (check == NULL || ft_strncmp(".cub", check, 5) != 0)
	{
		printf("\033[0;31m""Error \nMap is not a .cub format!\n""\033[0m");
		exit(1);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[0;31m""Error \nFile descriptor is not valid!\n""\033[0m");
		exit(1);
	}
	return (fd);
}
