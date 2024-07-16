/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:35:57 by eandre            #+#    #+#             */
/*   Updated: 2024/07/16 18:29:21 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	static t_game	game;

	
	game = game_init(argc, argv);
	(void)game;
}

t_config	config_init(void)
{
	t_config	config;
	
	config.north_path = NULL;
	config.east_path = NULL;
	config.west_path = NULL;
	config.south_path = NULL;
	config.floor_color = NULL;
	config.ceiling_color = NULL;
	return (config);
}

t_game	game_init(int argc, char **argv)
{
	int		fd;
	t_game	game;

	fd = error_manager(argc, argv[1]);
	game.config = config_init();
	parse_map(fd, &game.config);
	return (game);
}

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

void	parse_map(int fd, t_config *config)
{
	char	*gnl;

	gnl = get_next_line(fd);
	if (gnl == NULL)
	{
		printf("\033[0;31m""Error \nMap is empty!\n""\033[0m");
		close(fd);
		exit (1);
	}
	while (parse_line(gnl, config) == 1)
		gnl = get_next_line(fd);
	printf("%s\n", config->north_path);
	free(gnl);
	free(config->north_path);
	close(fd);
}

int	parse_line(char *gnl, t_config *config)
{
	if (gnl == NULL)
	{
		free(gnl);
		return (0);
	}
	if (ft_strncmp(gnl, "NO ", 3) == 0 && config->north_path != NULL)
	{
		printf("\033[0;31m""Error \nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		free(gnl);
		free(config->north_path);
		exit (1);
	}
	if (ft_strncmp(gnl, "NO ", 3) == 0 && gnl[3] != '\0')
		config->north_path = ft_strdup(&gnl[3]);
	free(gnl);
	return (1);
}
