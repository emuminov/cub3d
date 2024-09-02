/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:11:26 by eandre            #+#    #+#             */
/*   Updated: 2024/09/02 19:49:09 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/math_funcs.h"
#include "../include/constants.h"
#include "./minilibx-linux/mlx.h"
#include <stddef.h>
#include <stdio.h>

int	start_game(int argc, char **argv)
{
	static t_game		g;

	extract_params_from_cub_file(&g, argc, argv);
	g.mlx = mlx_init();
	if (g.mlx == NULL)
		return (printf("\033[0;31m" \
		"Error\nFailed to initialize mlx!\n""\033[0m"), free_game(&g), 1);
	g.window_size = vectori(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (init_wall_textures(&g) == 1)
		return (printf("\033[0;31m" \
		"Error\nFailed to initialize walls!\n""\033[0m"), free_game(&g), 1);
	if (init_animation_textures(&g) == 1)
		return (printf("\033[0;31m" \
		"Error\nFailed to initialize animation!\n""\033[0m"), free_game(&g), 1);
	if (create_window(&g) == 1)
		return (printf("\033[0;31m" \
		"Error\nFailed to initialize window!\n""\033[0m"), free_game(&g), 1);
	start_game_loop(&g);
	return (0);
}

int	main(int argc, char **argv)
{
	return (start_game(argc, argv));
}
