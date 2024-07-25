/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:16:25 by eandre            #+#    #+#             */
/*   Updated: 2024/07/25 16:04:45 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/libft/libft.h"
# include "../src/libft/ft_printf/ft_printf.h"
# include "../src/libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_config_parsing
{
	char	*north_path;
	char	*east_path;
	char	*south_path;
	char	*west_path;
	int		map_fd;
	int		*floor_c;
	int		*ceiling_c;
}	t_config_parsing;

typedef struct s_config
{
	int		north_fd;
	int		east_fd;
	int		south_fd;
	int		west_fd;
	int		*floor_c;
	int		*ceiling_c;
}	t_config;


typedef struct s_game
{
	char		**map;
	char		*map_1d;
	t_config	conf;
}	t_game;


unsigned char		ft_atoc(const char *str, char *gnl, t_config_parsing *conf);
int					charcmp(char *str, char c);
int					error_manager(int argc, char *argv);
int					parse_line_keys(char *gnl, t_config_parsing *conf);
void				parse_map(int fd, t_config_parsing *conf, t_game *game);
t_config_parsing	config_parsing_init(void);
t_config			config_init(void);
void				free_config(t_config *conf);
void				paths_errors(t_config_parsing *conf);
t_game				game_init(int argc, char **argv);
void				free_config_p(t_config_parsing *conf);
int					error_key(char *gnl, t_config_parsing *conf, int i, int strcmp_value);
void				open_paths(t_config_parsing *conf_p, t_config *conf);

#endif
