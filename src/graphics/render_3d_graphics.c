/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:42:10 by eandre            #+#    #+#             */
/*   Updated: 2024/09/02 19:32:06 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/graphics.h"
#include "../../include/math_funcs.h"
#include "../minilibx-linux/mlx.h"
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#include <math.h>

static void	draw_fog(t_game *g, t_graphics *graph, int x);
static void	get_texture(t_game *g, t_graphics *graph,
				t_vectorf *ray_dir);
static void	calcul_drawing_values(t_game *g, t_graphics *graph,
				t_vectorf *ray_dir);
static void	draw_walls(t_game *g, t_graphics *graph, int x, t_vectorf *ray_dir);

void	render_3d_graphics(t_game *g)
{
	t_graphics		graph;
	int				x;
	double			cam_x;
	t_vectorf		ray_dir;

	draw_ceiling_and_floor(&g->frame, g->conf.ceil_c, g->conf.floor_c);
	x = 0;
	while (x < g->window_size.x)
	{
		cam_x = 2 * x / (double)g->window_size.x - 1;
		ray_dir = vectorf_add(g->player.dir, vectorf_scale(g->player.plane,
					cam_x));
		check_cell_in_dir(g, ray_dir, MAX_WALL_DISTANCE, "1D");
		g->rays[x] = g->dp.last_cell;
		calcul_drawing_values(g, &graph, &ray_dir);
		get_texture(g, &graph, &ray_dir);
		if (g->dp.is_cell_found)
			draw_walls(g, &graph, x, &ray_dir);
		else
			draw_fog(g, &graph, x);
		x++;
	}
	draw_minimap(g);
	render_hands(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

static void	draw_fog(t_game *g, t_graphics *graph, int x)
{
	int				y;

	y = graph->draw_start;
	while (y < graph->draw_end)
	{
		put_pixel_on_img(&g->frame, vectori(x, y), g->conf.ceil_c);
		y++;
	}
}

static void	draw_walls(t_game *g, t_graphics *graph, int x, t_vectorf *ray_dir)
{
	int				y;
	double			texture_pos;
	double			step;

	y = graph->draw_start;
	graph->tex_point.x = (int)(graph->wall_x_point
			* (double)graph->texture->dimensions.x);
	if ((g->dp.side == 0 && ray_dir->x > 0) || (g->dp.side == 1
			&& ray_dir->y < 0))
		graph->tex_point.x = graph->texture
			->dimensions.x - graph->tex_point.x - 1;
	step = 1.0 * graph->texture->dimensions.y
		/ graph->line_height;
	texture_pos = (graph->draw_start - (double)g->window_size.y / 2
			+ (double)graph->line_height / 2) * step;
	while (y < graph->draw_end)
	{
		graph->tex_point.y = (int)texture_pos;
		texture_pos += step;
		put_pixel_on_img(&g->frame, vectori(x, y),
			mix_rgb(g->conf.ceil_c, get_pixel_of_img(*graph->texture,
					graph->tex_point),
				graph->fog_percentage));
		y++;
	}
}

static void	get_texture(t_game *g, t_graphics *graph,
		t_vectorf *ray_dir)
{
	if (g->dp.type_of_found_cell == wall)
	{
		if (g->dp.side == 0)
		{
			if (ray_dir->x < 0)
				graph->texture = &g->wall_textures[west_tex];
			else
				graph->texture = &g->wall_textures[east_tex];
		}
		else
		{
			if (ray_dir->y > 0)
				graph->texture = &g->wall_textures[south_tex];
			else
				graph->texture = &g->wall_textures[north_tex];
		}
	}
	else if (g->dp.type_of_found_cell == door_closed)
		graph->texture = &g->door_texture;
}

static void	calcul_drawing_values(t_game *g, t_graphics *graph,
		t_vectorf *ray_dir)
{
	graph->line_height = (int)(g->window_size.y / g->dp.distance);
	graph->draw_start = -graph->line_height / 2 + g->window_size.y / 2;
	if (graph->draw_start < 0)
		graph->draw_start = 0;
	graph->draw_end = graph->line_height / 2 + g->window_size.y / 2;
	if (graph->draw_end >= g->window_size.y)
		graph->draw_end = g->window_size.y - 1;
	if (g->dp.side == 0)
		graph->wall_x_point = g->player.pos.y + g->dp.distance * ray_dir->y;
	else
		graph->wall_x_point = g->player.pos.x + g->dp.distance * ray_dir->x;
	graph->wall_x_point -= floor(graph->wall_x_point);
	if (g->dp.distance > MAX_WALL_DISTANCE)
		graph->fog_percentage = 1.0;
	else
		graph->fog_percentage = g->dp.distance / MAX_WALL_DISTANCE;
}
