/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:35:57 by eandre            #+#    #+#             */
/*   Updated: 2024/07/25 11:50:11 by eandre           ###   ########.fr       */
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

void	parse_map(int fd, t_config_parsing *conf)
{
	char	*gnl;

	gnl = get_next_line(fd);
	if (gnl == NULL)
	{
		printf("\033[0;31m""Error \nMap is empty!\n""\033[0m");
		close(fd);
		exit (1);
	}
	while (parse_line(gnl, conf) == 1)
		gnl = get_next_line(fd);
	free(gnl);
	printf("north value : %s, east value : %s, south value : %s, west value : %s\n", conf->north_path, conf->east_path, conf->south_path, conf->west_path);
	if (conf->floor_c != NULL)
		printf("%d, %d, %d\n", conf->floor_c[0], conf->floor_c[1], conf->floor_c[2]);
	if (conf->ceiling_c != NULL)
		printf("%d, %d, %d\n", conf->ceiling_c[0], conf->ceiling_c[1], conf->ceiling_c[2]);
	close(fd);
}

void	north_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "NO", 2) != 0)
		return ;
	if (error_key(gnl, conf, 2, ft_strncmp(gnl, "NO", 2) == 0) == 1)
		return ;
	if (conf->north_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1));
	}
	conf->north_path = ft_strdup(&gnl[3]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->north_path[ft_strlen(conf->north_path) - 1] = '\0';
}

int	error_key(char *gnl, t_config_parsing *conf, int i, int strcmp_value)
{
	if (gnl[i] != '\0' && gnl[i] != '\n' && gnl[i] != ' ')
		return (1);
	else if (gnl[i] == '\0' || gnl[i] == '\n')
		printf("\033[0;31m"
			"Error\nOne of the value of a key is empty!\n""\033[0m");
	else
	{
		if (gnl[i] == ' ')
			i++;
		if (gnl[i] == '\n' || gnl[i] == '\0')
			printf("\033[0;31m"
				"Error\nOne of the value of a key is empty!\n""\033[0m");
		else if (ft_isspace(gnl[i]) == 1)
			printf("\033[0;31m"
				"Error\nOnly one space is needed after a key!\n""\033[0m");
		else if (strcmp_value == 1)
			return (0);
	}
	get_next_line(-1);
	return (free(gnl), free_config_p(conf), exit(1), 1);
}

void	east_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "EA", 2) != 0)
		return ;
	if (error_key(gnl, conf, 2, ft_strncmp(gnl, "EA", 2) == 0) == 1)
		return ;
	if (conf->east_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1));
	}
	conf->east_path = ft_strdup(&gnl[3]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->east_path[ft_strlen(conf->east_path) - 1] = '\0';
}

void	west_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "WE", 2) != 0)
		return ;
	if (error_key(gnl, conf, 2, ft_strncmp(gnl, "WE", 2) == 0) == 1)
		return ;
	if (conf->west_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1));
	}
	conf->west_path = ft_strdup(&gnl[3]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->west_path[ft_strlen(conf->west_path) - 1] = '\0';
}

void	south_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "SO", 2) != 0)
		return ;
	if (error_key(gnl, conf, 2, ft_strncmp(gnl, "SO", 2) == 0) == 1)
		return ;
	if (conf->south_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1));
	}
	conf->south_path = ft_strdup(&gnl[3]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->south_path[ft_strlen(conf->south_path) - 1] = '\0';
}

void	ceiling_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "C", 1) != 0)
		return ;
	if (error_key(gnl, conf, 1, ft_strncmp(gnl, "C", 1) == 0) == 1)
		return ;
	if (conf->ceiling_c != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1));
	}
	if (ft_strchr(&gnl[2], ',') != NULL && ft_strrchr(gnl, ',') != NULL)
	{
		conf->ceiling_c = calloc(3, sizeof(int));
		conf->ceiling_c[0] = ft_atoc(&gnl[2], gnl, conf);
		conf->ceiling_c[1] = ft_atoc(ft_strchr(&gnl[2], ',') + 1, gnl, conf);
		conf->ceiling_c[2] = ft_atoc(ft_strrchr(gnl, ',') + 1, gnl, conf);
	}
	if (charcmp(gnl, ',') != 2)
	{
		printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1));
	}
}

void	path_format_checker(char *str, t_config_parsing *conf);

void	paths_errors(t_config_parsing *conf)
{
	if (!conf->east_path || !conf->north_path || !conf->south_path || !conf->west_path || !conf->floor_c || !conf->ceiling_c)
	{
		printf("\033[0;31m""Error\nA key is missing!\n""\033[0m");
		free_config_p(conf);
		exit (1);
	}
	path_format_checker(conf->east_path, conf);
	path_format_checker(conf->north_path, conf);
	path_format_checker(conf->south_path, conf);
	path_format_checker(conf->west_path, conf);
}

void	path_format_checker(char *str, t_config_parsing *conf)
{
	char	*check;

	check = ft_strnstr(str, ".xpm", ft_strlen(str));
	if (check == NULL || ft_strncmp(".xpm", check, 5) != 0)
	{
		printf("\033[0;31m""Error \nOne of the textures is not in a .xpm format!\n""\033[0m");
		free_config_p(conf);
		exit(1);
	}
}

void	floor_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "F", 1) != 0)
		return ;
	if (error_key(gnl, conf, 1, ft_strncmp(gnl, "F", 1) == 0) == 1)
		return ;
	if (conf->floor_c != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1));
	}
	if (ft_strchr(&gnl[2], ',') != NULL && ft_strrchr(gnl, ',') != NULL)
	{
		conf->floor_c = calloc(3, sizeof(int));
		conf->floor_c[0] = ft_atoc(&gnl[2], gnl, conf);
		conf->floor_c[1] = ft_atoc(ft_strchr(&gnl[2], ',') + 1, gnl, conf);
		conf->floor_c[2] = ft_atoc(ft_strrchr(gnl, ',') + 1, gnl, conf);
	}
	if (charcmp(gnl, ',') != 2)
	{
		printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1));
	}
}

void	open_paths(t_config_parsing *conf_p, t_config *conf)
{
	conf->east_fd = open(conf_p->east_path, O_RDONLY);
	if (conf->east_fd == -1)
	{
		printf("\033[0;31m"
			"Error\nEast path: %s: no such file or directory!\n""\033[0m",
			conf_p->east_path);
		return (free_config_p(conf_p), free_config(conf), exit (1));
	}
	conf->north_fd = open(conf_p->north_path, O_RDONLY);
	if (conf->north_fd == -1)
	{
		printf("\033[0;31m"
			"Error\nNorth path: %s: no such file or directory!\n""\033[0m",
			conf_p->north_path);
		return (free_config_p(conf_p), free_config(conf), exit (1));
	}
	conf->west_fd = open(conf_p->west_path, O_RDONLY);
	if (conf->west_fd == -1)
	{
		printf("\033[0;31m"
			"Error\nWest path: %s: no such file or directory!\n""\033[0m",
			conf_p->west_path);
		return (free_config_p(conf_p), free_config(conf), exit (1));
	}
	conf->south_fd = open(conf_p->south_path, O_RDONLY);
	if (conf->south_fd == -1)
	{
		printf("\033[0;31m"
			"Error\nSouth path: %s: no such file or directory!\n""\033[0m",
			conf_p->south_path);
		return (free_config_p(conf_p), free_config(conf), exit (1));
	}
}

int	parse_line(char *gnl, t_config_parsing *conf)
{
	if (gnl == NULL)
		return (0);
	north_key_manager(gnl, conf);
	south_key_manager(gnl, conf);
	east_key_manager(gnl, conf);
	west_key_manager(gnl, conf);
	floor_key_manager(gnl, conf);
	ceiling_key_manager(gnl, conf);
	free(gnl);
	return (1);
}
