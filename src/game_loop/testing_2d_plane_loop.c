/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_2d_plane_loop.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:19:45 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/18 23:47:28 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"

// static void	render_2d_plane_graphic(t_game *g);
static int	testing_2d_plane_loop(t_game *g);
static void	create_basic_map(t_game *g);
static void	render_minimap_graphic(t_game *g);

/* Draws a simple 2d plane for testing purposes
 * TODO: check for possible memory failures */
int	init_testing_2d_plane_loop(void)
{
	static t_game	g;

	init_game(&g, 640, 640);
	create_basic_map(&g);
	render_minimap_graphic(&g);
	mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);
	mlx_hook(g.win, 2, (1L << 0), handle_key_press, &g);
	mlx_hook(g.win, 3, (1L << 1), handle_key_release, &g);
	mlx_loop_hook(g.mlx, testing_2d_plane_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}

static void	render_minimap_graphic(t_game *g)
{
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

/* Update and render loop for testing 2d plane */
static int	testing_2d_plane_loop(t_game *g)
{
	if (is_any_key_pressed(g))
	{
		update_game_state(g);
		render_minimap_graphic(g);
	}
	return (0);
}

static void	create_basic_map(t_game *g)
{
	int	x;
	int	y;

	g->map = ft_calloc(10, sizeof(char *));
	y = 0;
	while (y < 10)
	{
		g->map[y] = ft_calloc(10, sizeof(char));
		x = 0;
		while (x < 10)
		{
			if (x == 0 || x == 9 || y == 0 || y == 9)
				g->map[y][x] = '1';
			else
				g->map[y][x] = '0';
			x++;
		}
		y++;
	}
	g->map[3][5] = '2';
	g->map[3][2] = '1';
	g->map[1][2] = '1';
}
