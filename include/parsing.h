/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:34:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 02:44:22 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3d.h"
# include <stddef.h>
typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_stack_stats
{
	int		stack_size;
	int		len_strs;
	int		*len_tab;
	t_coord	*stack;
}	t_stack_stats;

/*					// PARSE \\					*/
int					parse_line(char *gnl, t_config_parsing *conf);
void				pre_parsing(int fd, t_config_parsing *conf);
int					parse_map(char **map);
/*					// INNIT \\					*/
t_config_parsing	config_parsing_init(void);
t_config			config_init(void);
t_game				game_init(int argc, char **argv);
int					stack_stats_init(t_stack_stats *stack_stats, int len_strs,
					int *len_tab, t_coord cur);
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
/*					// MAP MANAGEMENT \\					*/
void				manage_inturn_fill(t_stack_stats *stack_s,
					t_coord cur, int *inturn);
void				manage_xy_fill(char **tab, t_stack_stats *stack_s,
					t_coord cur);
int					cur_border_checker(t_coord cur, int *len_tab, int len_strs);
int					fill(char **tab, int len_strs, t_coord cur, int *len_tab);
/*					// PATH MANAGEMENT \\					*/
void				paths_errors(t_config_parsing *conf);
void				path_format_checker(char *str, t_config_parsing *conf);
void				open_paths(t_config_parsing *conf_p, t_config *conf);
int					error_manager(int argc, char *argv);
void				open_error_manager(t_config_parsing *conf_p, t_config *conf,
						char *path, char *name);
/*					// UTILS \\					*/
int					ft_atoc(const char *str, char *gnl, t_config_parsing *conf);
int					charcmp(char *str, char c);
char				*ft_strjoin_free(char *s1, char *s2);
t_coord				get_start(char **map);
size_t				ft_strslen(char **strs);
/*					// FREE \\					*/
void				free_config_p(t_config_parsing *conf);
void				free_config(t_config *conf);
void				free_tab(char **tab);
#endif
