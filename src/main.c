/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:11:26 by eandre            #+#    #+#             */
/*   Updated: 2024/08/28 19:50:15 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/constants.h"
#include "./minilibx-linux/mlx.h"
#include <stddef.h>

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
	extract_params_from_cub_file(&g, argc, argv);
	g.mlx = mlx_init();
	if (g.mlx == NULL)
		return (1); // TODO: cleanup the memory
	init_textures(&g);
	if (create_window(&g) == 1)
		return (1); // TODO: cleanup the memory
	start_game_loop(&g);
	return (0);
}

int	main(int argc, char **argv)
{
	return _old_start_game(argc, argv);
}
