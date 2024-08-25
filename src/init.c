/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:31:49 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 02:35:56 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/constants.h"

int	init_game_loop(int argc, char **argv)
{
	static t_game		g;

	parse_cub_map(&g, argc, argv);
	init_game(&g, WINDOW_WIDTH, WINDOW_HEIGHT);
	return (0);
}
