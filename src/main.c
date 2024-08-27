/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:11:26 by eandre            #+#    #+#             */
/*   Updated: 2024/08/27 18:45:12 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/constants.h"
#include "./minilibx-linux/mlx.h"

int	_old_start_game(int argc, char **argv)
{
	static t_game		g;

	extract_params_from_cub_file(&g, argc, argv);
	_old_start_mlx(&g, WINDOW_WIDTH, WINDOW_HEIGHT);
	return (0);
}

/* Function to fix: this is going to be our function that starts everything */
// we also need initialize player's staring position, plane, direction
int	start_game(int argc, char **argv)
{
	static t_game		g;

	(void)argc;
	(void)argv;
	//1. Do parsing
	g.mlx = mlx_init();
	//2. Init textures
	create_window(&g);
	start_game_loop(&g);
	return (0);
}

int	main(int argc, char **argv)
{
	return _old_start_game(argc, argv);
}
