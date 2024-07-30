/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:16:25 by eandre            #+#    #+#             */
/*   Updated: 2024/07/30 19:10:36 by eandre           ###   ########.fr       */
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
	char	*map_1d;
	int		keys_finish;
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
	t_config	conf;
}	t_game;

/*					// PARSE \\					*/
int					parse_line(char *gnl, t_config_parsing *conf);
void				pre_parsing(int fd, t_config_parsing *conf);
/*					// INNIT \\					*/
t_config_parsing	config_parsing_init(void);
t_config			config_init(void);
t_game				game_init(int argc, char **argv);
/*					// KEY MANAGEMENT \\					*/
int					north_key_manager(char *gnl, t_config_parsing *conf);
int					east_key_manager(char *gnl, t_config_parsing *conf);
int					west_key_manager(char *gnl, t_config_parsing *conf);
int					south_key_manager(char *gnl, t_config_parsing *conf);
int					ceiling_key_manager(char *gnl, t_config_parsing *conf);
int					floor_key_manager(char *gnl, t_config_parsing *conf);
int					error_key(char *gnl, t_config_parsing *conf,
						int i, int strcmp_value);
int					key_finish_check(char *gnl, t_config_parsing *conf);
/*					// PATH MANAGEMENT \\					*/
void				paths_errors(t_config_parsing *conf);
void				path_format_checker(char *str, t_config_parsing *conf);
void				open_paths(t_config_parsing *conf_p, t_config *conf);
int					error_manager(int argc, char *argv);
void				open_error_manager(t_config_parsing *conf_p, t_config *conf,
						char *path, char *name);
/*					// UTILS \\					*/
unsigned char		ft_atoc(const char *str, char *gnl, t_config_parsing *conf);
int					charcmp(char *str, char c);
char				*ft_strjoin_free(char *s1, char *s2);
/*					// FREE \\					*/
void				free_config_p(t_config_parsing *conf);
void				free_config(t_config *conf);
void				free_tab(char **tab);

#endif
