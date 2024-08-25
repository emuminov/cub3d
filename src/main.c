/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:11:26 by eandre            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/25 19:10:44 by emuminov         ###   ########.fr       */
=======
/*   Updated: 2024/08/25 18:17:38 by emuminov         ###   ########.fr       */
>>>>>>> 9dd63b6 (refactor: removed minimap_size on the game struct, partially normalized the minimap code, fixed wobbling on the walls drawing, merged main.c with init.c)
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/constants.h"
#include "./minilibx-linux/mlx.h"

int	_old_start_game(int argc, char **argv)
{
	static t_game		g;

	parse_cub_map(&g, argc, argv);
	_old_start_mlx(&g, WINDOW_WIDTH, WINDOW_HEIGHT);
	return (0);
}

/* Function to fix: this is going to be our function that starts everything */
// we also need initialize player's staring position, plane, direction
int	start_game(int argc, char **argv)
{
	static t_game		g;
<<<<<<< HEAD

	(void)argc;
	(void)argv;
=======
	int					dummy_mouse_pos_y;

	(void)argc;
	(void)argv;
	(void)dummy_mouse_pos_y;
>>>>>>> 9dd63b6 (refactor: removed minimap_size on the game struct, partially normalized the minimap code, fixed wobbling on the walls drawing, merged main.c with init.c)
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
