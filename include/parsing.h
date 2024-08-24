/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:34:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 00:37:16 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3d.h"
#include "cub3d.h"

/*					// PARSE \\								*/
int					parse_line(char *gnl, t_config_parsing *conf);
void				pre_parsing(int fd, t_config_parsing *conf);
void				parse_map(char **map);
/*					// INNIT \\								*/
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
int					error_key(char *gnl, t_config_parsing *conf, int i,
						int strcmp_value);
int					key_finish_check(char *gnl, t_config_parsing *conf);
/*					// PATH MANAGEMENT \\					*/
void				paths_errors(t_config_parsing *conf_p, t_config *conf);
void				path_format_checker(char *str, t_config_parsing *conf);
void				open_paths(t_config_parsing *conf_p, t_config *conf);
int					error_manager(int argc, char *argv);
void				open_error_manager(t_config_parsing *conf_p, t_config *conf,
						char *path, char *name);
/*					// UTILS \\								*/
unsigned char		ft_atoc(const char *str, char *gnl, t_config_parsing *conf);
int					charcmp(char *str, char c);
char				*ft_strjoin_free(char *s1, char *s2);
#endif
