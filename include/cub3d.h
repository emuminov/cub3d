/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:16:25 by eandre            #+#    #+#             */
/*   Updated: 2024/07/18 15:55:25 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/libft/libft.h"
# include "../src/libft/ft_printf/ft_printf.h"
# include "../src/libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_config
{
	char	*north_path;
	char	*east_path;
	char	*south_path;
	char	*west_path;
	int		*floor_c;
	int		*ceiling_c;
}	t_config;

typedef struct s_game
{
	char		**map;
	t_config	conf;
}	t_game;


unsigned char	ft_atoc(const char *str, char *gnl, t_config *conf);
int				charcmp(char *str, char c);
int				error_manager(int argc, char *argv);
int				parse_line(char *gnl, t_config *conf);
void			parse_map(int fd, t_config *conf);
t_config		config_init(void);
t_game			game_init(int argc, char **argv);
void			free_config(t_config *conf);
int				error_key(char *gnl, t_config *conf, int i, int strcmp_value);

#endif
