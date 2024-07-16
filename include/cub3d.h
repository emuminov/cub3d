/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:16:25 by eandre            #+#    #+#             */
/*   Updated: 2024/07/16 18:00:59 by eandre           ###   ########.fr       */
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
	int		*floor_color;
	int		*ceiling_color;
}	t_config;

typedef struct s_game
{
	char		**map;
	t_config	config;
}	t_game;


int			error_manager(int argc, char *argv);
int			parse_line(char *gnl, t_config *config);
void		parse_map(int fd, t_config *config);
t_config	config_init(void);
t_game		game_init(int argc, char **argv);

#endif
