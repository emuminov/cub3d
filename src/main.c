/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:35:57 by eandre            #+#    #+#             */
/*   Updated: 2024/08/01 17:36:24 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	static t_game	game;
	int				i;

	i = 0;
	game = game_init(argc, argv);
	while (game.map[i])
	{
		printf("%s\n", game.map[i]);
		i++;
	}
	free_tab(game.map);
}
