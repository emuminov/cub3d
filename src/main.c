/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:35:57 by eandre            #+#    #+#             */
/*   Updated: 2024/07/26 16:45:31 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	static t_game	game;
	int				i;

	i = 0;
	game = game_init(argc, argv);
	while(game.map[i])
	{
		printf("%s\n", game.map[i]);
		i++;
	}
	free_tab(game.map);
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
	conf->map_fd = fd;
	if (gnl == NULL)
	{
		printf("\033[0;31m""Error \nMap is empty!\n""\033[0m");
		close(fd);
		exit (1);
	}
	while (parse_line(gnl, conf) == 1)
		gnl = get_next_line(fd);
	free(gnl);
	close(fd);
	if (conf->keys_finished == 0)
		return (free_config_p(conf), printf("\033[0;31m""Error \nThe map contains only keys!\n""\033[0m"), exit(1));
	printf("north value : %s, east value : %s, south value : %s, west value : %s\n", conf->north_path, conf->east_path, conf->south_path, conf->west_path);
	if (conf->floor_c != NULL)
		printf("%d, %d, %d\n", conf->floor_c[0], conf->floor_c[1], conf->floor_c[2]);
	if (conf->ceiling_c != NULL)
		printf("%d, %d, %d\n", conf->ceiling_c[0], conf->ceiling_c[1], conf->ceiling_c[2]);
}

int	north_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "NO", 2) != 0)
		return (0);
	if (error_key(gnl, conf, 2, ft_strncmp(gnl, "NO", 2) == 0) == 1)
		return (0);
	if (conf->north_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	conf->north_path = ft_strdup(&gnl[3]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->north_path[ft_strlen(conf->north_path) - 1] = '\0';
	return (1);
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

int	east_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "EA", 2) != 0)
		return (0);
	if (error_key(gnl, conf, 2, ft_strncmp(gnl, "EA", 2) == 0) == 1)
		return (0);
	if (conf->east_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	conf->east_path = ft_strdup(&gnl[3]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->east_path[ft_strlen(conf->east_path) - 1] = '\0';
	return (1);
}

int	west_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "WE", 2) != 0)
		return (0);
	if (error_key(gnl, conf, 2, ft_strncmp(gnl, "WE", 2) == 0) == 1)
		return (0);
	if (conf->west_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	conf->west_path = ft_strdup(&gnl[3]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->west_path[ft_strlen(conf->west_path) - 1] = '\0';
	return (1);
}

int	south_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "SO", 2) != 0)
		return (0);
	if (error_key(gnl, conf, 2, ft_strncmp(gnl, "SO", 2) == 0) == 1)
		return (0);
	if (conf->south_path != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	conf->south_path = ft_strdup(&gnl[3]);
	if (gnl[ft_strlen(gnl) - 1] == '\n')
		conf->south_path[ft_strlen(conf->south_path) - 1] = '\0';
	return (1);
}

int	ceiling_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "C", 1) != 0)
		return (0);
	if (error_key(gnl, conf, 1, ft_strncmp(gnl, "C", 1) == 0) == 1)
		return (0);
	if (conf->ceiling_c != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
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
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	return (1);
}

void	path_format_checker(char *str, t_config_parsing *conf);

void	paths_errors(t_config_parsing *conf)
{
	if (!conf->east_path || !conf->north_path || !conf->south_path
		|| !conf->west_path || !conf->floor_c || !conf->ceiling_c)
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
		printf("\033[0;31m"
			"Error \nOne of the textures is not in a .xpm format!\n""\033[0m");
		free_config_p(conf);
		exit(1);
	}
}

int	floor_key_manager(char *gnl, t_config_parsing *conf)
{
	if (ft_strncmp(gnl, "F", 1) != 0)
		return (0);
	if (error_key(gnl, conf, 1, ft_strncmp(gnl, "F", 1) == 0) == 1)
		return (0);
	if (conf->floor_c != NULL)
	{
		printf("\033[0;31m""Error\nDouble keys are not allowed!\n""\033[0m");
		get_next_line(-1);
		return (free(gnl), free_config_p(conf), exit(1), 0);
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
		return (free(gnl), free_config_p(conf), exit(1), 0);
	}
	return (1);
}

void	open_error_manager(t_config_parsing *conf_p, t_config *conf,
char *path, char *name)
{
	printf("\033[0;31m"
		"Error\n%s path: %s: no such file or directory!\n""\033[0m", name,
		path);
	free_config_p(conf_p);
	free_config(conf);
	exit(1);
}

void	open_paths(t_config_parsing *conf_p, t_config *conf)
{
	conf->east_fd = open(conf_p->east_path, O_RDONLY);
	if (conf->east_fd == -1)
		open_error_manager(conf_p, conf, conf_p->east_path, "East");
	conf->north_fd = open(conf_p->north_path, O_RDONLY);
	if (conf->north_fd == -1)
		open_error_manager(conf_p, conf, conf_p->north_path, "North");
	conf->west_fd = open(conf_p->west_path, O_RDONLY);
	if (conf->west_fd == -1)
		open_error_manager(conf_p, conf, conf_p->west_path, "West");
	conf->south_fd = open(conf_p->south_path, O_RDONLY);
	if (conf->south_fd == -1)
		open_error_manager(conf_p, conf, conf_p->south_path, "South");
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*strs;
	size_t	len;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	strs = malloc(sizeof(char) * (len + 1));
	if (strs == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		strs[i] = s1[i];
	j = 0;
	while (s2[j])
		strs[i++] = s2[j++];
	strs[i] = '\0';
	free(s1);
	return (strs);
}

// ===TO DO===
// check if there is no keys that are equal to gnl (= error of config)
//

int	map_manager(char *gnl, t_config_parsing *conf)
{
	int	i;

	i = 0;
	if ((!conf->east_path || !conf->north_path || !conf->south_path
		|| !conf->west_path || !conf->floor_c || !conf->ceiling_c))
		return (0);
	if (((ft_strncmp(gnl, "SO", 2) == 0 && (gnl[2] == '\0' || gnl[2] == '\n' || gnl[2] == ' '))
		|| (ft_strncmp(gnl, "NO", 2) == 0 && (gnl[2] == '\0' || gnl[2] == '\n' || gnl[2] == ' '))
		|| (ft_strncmp(gnl, "EA", 2) == 0 && (gnl[2] == '\0' || gnl[2] == '\n' || gnl[2] == ' '))
		|| (ft_strncmp(gnl, "WE", 2) == 0 && (gnl[2] == '\0' || gnl[2] == '\n' || gnl[2] == ' '))
		|| (ft_strncmp(gnl, "C", 1) == 0 && (gnl[1] == '\0' || gnl[1] == '\n' || gnl[1] == ' '))
		|| (ft_strncmp(gnl, "F", 1) == 0 && (gnl[1] == '\0' || gnl[1] == '\n' || gnl[1] == ' '))) && conf->keys_finished == 0)
		return (0);
	while (gnl[i])
	{
		if (ft_strchr(" 01NESW\n", gnl[i]) == NULL)
		{
			printf("\033[0;31m""Error\nUnrecognized character in map!\n""\033[0m");
			get_next_line(-1);
			return (free_config_p(conf), free(gnl), exit(1), 0);
		}
		i++;
	}
	conf->map_1d = ft_strjoin_free(conf->map_1d, gnl);
	return (1);
}


int	parse_line(char *gnl, t_config_parsing *conf_p)
{
	int	key_rv;

	key_rv = 0;
	if (gnl == NULL)
		return (0);
	if (conf_p->keys_finished == 0)
	{
		key_rv += north_key_manager(gnl, conf_p);
		key_rv += south_key_manager(gnl, conf_p);
		key_rv += east_key_manager(gnl, conf_p);
		key_rv += west_key_manager(gnl, conf_p);
		key_rv += floor_key_manager(gnl, conf_p);
		key_rv += ceiling_key_manager(gnl, conf_p);
	}
	conf_p->keys_finished += map_manager(gnl, conf_p);
	if (key_rv != 1 && (ft_strcmp(gnl, "\n") != 0) && conf_p->keys_finished == 0)
	{
		printf("\033[0;31m""Error\nUnrecognized character in keys!\n""\033[0m");
		get_next_line(-1);
		return (free_config_p(conf_p), free(gnl), exit(1), 0);
	}
	free(gnl);
	return (1);
}
