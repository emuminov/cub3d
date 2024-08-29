/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:34:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/30 00:05:54 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3d.h"
# include <stddef.h>

typedef struct s_config_parsing
{
	int				map_fd;
	char			paths[4][PATH_MAX];
	int				floor_c[3];
	int				ceil_c[3];
	char			*map_1d;
	int				are_keys_validated;
}					t_config_parsing;

typedef struct s_stack_stats
{
	int				stack_size;
	int				len_strs;
	int				*len_tab;
	t_vectori		*stack;
}					t_stack_stats;

/*					// PARSE \\					*/
int					parse_line(char *gnl, t_config_parsing *conf);
void				parse(t_config_parsing *conf);
int					validate_map_walls(char **map, t_game *g);

/*					// INNIT \\					*/
t_config_parsing	config_parsing_init(int fd);
t_game				game_init(int argc, char **argv);
int					stack_stats_init(t_stack_stats *stack_stats, int len_strs,
						int *len_tab, t_vectori cur);

/*					// KEY MANAGEMENT \\					*/
int					parse_north_key(char *gnl, t_config_parsing *conf);
int					parse_east_key(char *gnl, t_config_parsing *conf);
int					parse_west_key(char *gnl, t_config_parsing *conf);
int					parse_south_key(char *gnl, t_config_parsing *conf);
int					parse_ceiling_key(char *gnl, t_config_parsing *conf);
int					parse_floor_key(char *gnl, t_config_parsing *conf);
int					check_errors_keys(char *gnl, t_config_parsing *conf, int i,
						int strcmp_value);
int					key_finish_check(char *gnl, t_config_parsing *conf);

/*					// MAP MANAGEMENT \\					*/
void				manage_inturn_fill(t_stack_stats *stack_s, t_vectori cur,
						int *inturn);
void				manage_xy_fill(char **tab, t_stack_stats *stack_s,
						t_vectori cur);
int					cur_border_checker(t_vectori cur, int *len_tab,
						int len_strs);
int					check_holes(char **tab, int len_strs, t_vectori cur,
						int *len_tab);

/*					// PATH MANAGEMENT \\					*/
void				validate_keys(t_config_parsing *conf);
void				check_path_format(char *str, t_config_parsing *conf);
void				open_paths(t_config_parsing *conf_p, t_config *conf);
int					open_and_check_arg_errors(int argc, char *argv);
void				open_error_manager(t_config_parsing *conf_p, t_config *conf,
						char *path, char *name);

/*					// UTILS \\					*/
int					check_rgb(const char *str, char *gnl,
						t_config_parsing *conf);
int					charcmp(char *str, char c);
char				*ft_strjoin_free(char *s1, char *s2);
t_vectori			get_start(char **map);
size_t				ft_strslen(char **strs);

/*					// FREE \\					*/
void				free_config_p(t_config_parsing *conf);
void				free_tab(char **tab);
#endif
