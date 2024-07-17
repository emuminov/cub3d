/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:35:57 by eandre            #+#    #+#             */
/*   Updated: 2024/07/17 20:05:49 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	static t_game	game;

	game = game_init(argc, argv);
	(void)game;
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
	free(gnl);
	printf("north value : %s, east value : %s, south value : %s, west value : %s\n", config->north_path, config->east_path, config->south_path, config->west_path);
	printf("%d, %d, %d\n", config->floor_color[0], config->floor_color[1], config->floor_color[2]);
	printf("%d, %d, %d\n", config->ceiling_color[0], config->ceiling_color[1], config->ceiling_color[2]);
	free_config(config);
	close(fd);
}

void	north_key_manager(char *gnl, t_config *config)
{
	int	len;

	if (ft_strncmp(gnl, "NO ", 3) == 0 && config->north_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		free(gnl);
		free_config(config);
		exit (1);
	}
	if (ft_strncmp(gnl, "NO ", 3) == 0 && gnl[3] != '\0')
	{
		config->north_path = ft_strdup(&gnl[3]);
		len = ft_strlen(config->north_path);
		config->north_path[len - 1] = '\0';
	}
}

	// len = ft_strlen(gnl);
	// if (error_key(ft_strncmp(gnl, "NO", 2) == 0,
	// 	gnl, config, gnl[len - 1] == '\n') == 0)
	// {
	// 	config->north_path = ft_strdup(&gnl[3]);
	// 	len = ft_strlen(config->north_path);
	// 	if (config->north_path[len - 1] == '\n')
	// 		config->north_path[len - 1] = '\0';
	// }
int	error_key(int strcmp_bool, char *gnl, t_config *config, int has_n)
{
	int	i;

	i = 0;
	(void)i;
	(void)has_n;
	(void)strcmp_bool;
	return (0);
	get_next_line(-1);
	free(gnl);
	free_config(config);
	exit (1);
	return (1);
}
	// if (strcmp_bool && gnl[2] != '\0' && ft_isspace(gnl[2])
	// 	&& gnl[3] != '\0' && !ft_isspace(gnl[3]))
	// 	return (0);
	// if (strcmp_bool && config->north_path != NULL)
	// 	printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
	// else if (strcmp_bool && gnl[2] != '\0' && ft_isspace(gnl[3]) && !has_n)
	// 	printf("\033[0;31m""Error\nKILL YOURSELF!\n""\033[0m");
	// else if (strcmp_bool && gnl[2] != '\0' && !ft_isspace(gnl[3]) && !has_n)
	// 	printf("\033[0;31m"
	// 		"Error\nOne of the texture path is empty!\n""\033[0m");
	// else if (strcmp_bool && gnl[2] != '\0' && ft_isspace(gnl[3]) && has_n && gnl[3] == '\0')
	// 	printf("\033[0;31m""Error\nKILL YOURSELF!\n""\033[0m");
	// else if (strcmp_bool && gnl[2] != '\0' && !ft_isspace(gnl[3]) && has_n && gnl[3] != '\0' && gnl[4] == '\0')
	// 	printf("\033[0;31m"
	// 		"Error\nOne of the texture path is empty!\n""\033[0m");

void	east_key_manager(char *gnl, t_config *config)
{
	int	len;

	if (ft_strncmp(gnl, "EA ", 3) == 0 && config->east_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		free(gnl);
		free_config(config);
		exit (1);
	}
	if (ft_strncmp(gnl, "EA ", 3) == 0 && gnl[3] != '\0')
	{
		config->east_path = ft_strdup(&gnl[3]);
		len = ft_strlen(config->east_path);
		config->east_path[len - 1] = '\0';
	}
}

void	west_key_manager(char *gnl, t_config *config)
{
	int	len;

	if (ft_strncmp(gnl, "WE ", 3) == 0 && config->west_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		free(gnl);
		free_config(config);
		exit (1);
	}
	if (ft_strncmp(gnl, "WE ", 3) == 0 && gnl[3] != '\0')
	{
		config->west_path = ft_strdup(&gnl[3]);
		len = ft_strlen(config->west_path);
		config->west_path[len - 1] = '\0';
	}
}

void	south_key_manager(char *gnl, t_config *config)
{
	int	len;

	if (ft_strncmp(gnl, "SO ", 3) == 0 && config->south_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		free(gnl);
		free_config(config);
		exit (1);
	}
	if (ft_strncmp(gnl, "SO ", 3) == 0 && gnl[3] != '\0')
	{
		config->south_path = ft_strdup(&gnl[3]);
		len = ft_strlen(config->south_path);
		config->south_path[len - 1] = '\0';
	}
}

void	ceiling_key_manager(char *gnl, t_config *config)
{
	if (ft_strncmp(gnl, "C ", 2) == 0 && config->ceiling_color != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		free(gnl);
		free_config(config);
		exit (1);
	}
	if (ft_strncmp(gnl, "C ", 2) == 0 && gnl[2] != '\0')
	{
		config->ceiling_color = calloc(3, sizeof(int));
		config->ceiling_color[0] = ft_atoc(&gnl[2]);
		config->ceiling_color[1] = ft_atoc(ft_strchr(&gnl[2], ',') + 1);
		config->ceiling_color[2] = ft_atoc(ft_strrchr(gnl, ',') + 1);
		if (charcmp(gnl, ',') != 2)
		{
			printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m");
			get_next_line(-1);
			free(gnl);
			free_config(config);
			exit (1);
		}
	}
}

void	floor_key_manager(char *gnl, t_config *config)
{
	if (ft_strncmp(gnl, "F ", 2) == 0 && config->floor_color != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		free(gnl);
		free_config(config);
		exit (1);
	}
	if (ft_strncmp(gnl, "F ", 2) == 0 && gnl[2] != '\0')
	{
		config->floor_color = calloc(3, sizeof(int));
		config->floor_color[0] = ft_atoc(&gnl[2]);
		config->floor_color[1] = ft_atoc(ft_strchr(&gnl[2], ',') + 1);
		config->floor_color[2] = ft_atoc(ft_strrchr(gnl, ',') + 1);
		if (charcmp(gnl, ',') != 2)
		{
			printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m");
			get_next_line(-1);
			free(gnl);
			free_config(config);
			exit (1);
		}
	}
}

int	parse_line(char *gnl, t_config *config)
{
	if (gnl == NULL)
		return (0);
	north_key_manager(gnl, config);
	south_key_manager(gnl, config);
	east_key_manager(gnl, config);
	west_key_manager(gnl, config);
	floor_key_manager(gnl, config);
	ceiling_key_manager(gnl, config);
	free(gnl);
	return (1);
}
