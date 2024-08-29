/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:11:26 by eandre            #+#    #+#             */
/*   Updated: 2024/08/29 23:24:54 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/math_funcs.h"
#include "../include/constants.h"
#include "./minilibx-linux/mlx.h"
#include <stddef.h>

int	start_game(int argc, char **argv)
{
	static t_game		g;

	extract_params_from_cub_file(&g, argc, argv);
	g.mlx = mlx_init();
	if (g.mlx == NULL)
		return (1); // TODO: cleanup the memory
	g.window_size = vectori(WINDOW_WIDTH, WINDOW_HEIGHT);
	init_textures(&g);
	init_animations_path(&g);
	init_animations(&g, g.idle_textures, 6, g.idle_tex_path);
	init_animations(&g, g.walk_textures, 8, g.walk_tex_path);
	if (create_window(&g) == 1)
		return (1); // TODO: cleanup the memory
	start_game_loop(&g);
	return (0);
}

int	main(int argc, char **argv)
{
	return start_game(argc, argv);
}
