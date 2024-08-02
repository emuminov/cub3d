/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:16 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/02 20:19:23 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define TILE_SIZE 128

#include "../minilibx-linux/mlx.h"

const int map[10][10] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 2, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

/* All the relevant data to rendered images */
typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_vectorf
{
	double	x;
	double	y;
}				t_vectorf;

typedef struct	s_vectori
{
	int		x;
	int		y;
}				t_vectori;

typedef	t_vectorf t_grid_coordsf;
typedef	t_vectori t_pixel_point;
typedef	t_vectori t_grid_coordsi;

typedef struct	s_dda_params
{
	t_grid_coordsf	ray_step;
	t_grid_coordsf	delta;
	t_grid_coordsf	dist_until_first_side;
	t_grid_coordsi	inspected_grid;
	bool			found_wall;
	double			camera;
}				t_dda_params;

typedef struct	s_player
{
	t_grid_coordsf	pos;
	t_vectorf		dir;
	t_vectorf		plane;
}				t_player;

typedef struct	s_game
{
	void			*mlx;
	void			*win;
	t_img			frame;
	t_player		player;
	t_dda_params	dp;
	int				**map;
}				t_game;

void	put_pixel_on_img(t_img *img, t_pixel_point p, int color)
{
	char	*dst;

	dst = img->addr + (p.y * img->line_len + p.x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void paint_tile(t_img *frame, t_pixel_point p, int color)
{
	t_pixel_point	start;
	t_pixel_point	end;

	start.y = p.y * TILE_SIZE;
	start.x = p.x * TILE_SIZE;

	end.y = start.y + TILE_SIZE;
	end.x = start.x + TILE_SIZE;
	while (start.y < end.y)
	{
		start.x = p.x * TILE_SIZE;
		while (start.x < end.x)
		{
			put_pixel_on_img(frame, start, color);
			start.x++;
		}
		start.y++;
	}
}

t_vectorf	vectorf_sub(t_vectorf v1, t_vectorf v2)
{
	return (t_vectorf){.x=v1.x - v2.x, .y=v1.y - v2.y};
}

t_vectorf	vectorf_add(t_vectorf v1, t_vectorf v2)
{
	return (t_vectorf){.x=v1.x + v2.x, .y=v1.y + v2.y};
}

t_vectorf	vectorf_scale(t_vectorf v, double nbr)
{
	return (t_vectorf){.x=v.x * nbr, .y=v.y * nbr};
}

t_vectori	vectori_sub(t_vectori v1, t_vectori v2)
{
	return (t_vectori){.x=v1.x - v2.x, .y=v1.y - v2.y};
}

double	abs_f(double n)
{
	if (n < 0)
		return -n;
	return n;
}

t_vectorf	vectorf_abs(t_vectorf v)
{
	return (t_vectorf){.x = abs_f(v.x), .y = abs_f(v.y)};
}

int	max(int n1, int n2)
{
	if (n1 >= n2)
		return n1;
	return n2;
}

unsigned int	get_pixel_img(t_img img, int x, int y) {
	return (*(unsigned int *)((img.addr
			+ (y * img.line_len) + (x * img.bits_per_pixel / 8))));
}

/* DDA line drawing algorithm */
void	draw_line(t_img *frame, t_pixel_point start, t_pixel_point end)
{
	const t_pixel_point		delta = vectori_sub(end, start);
	const int				steps = max(abs(delta.x), abs(delta.y));
	t_vectorf				next_point;
	t_vectorf				inc;
	int						i;

	next_point = (t_vectorf){.x = start.x, .y = start.y};
	inc = (t_vectorf){.x = (double)delta.x / steps, .y = (double)delta.y / steps};

	i = 0;
	while (i < steps)
	{
		put_pixel_on_img(frame,
				(t_pixel_point){.x = round(next_point.x), .y = round(next_point.y)},
				0x00A0FF);
		next_point.x += inc.x;
		next_point.y += inc.y;
		i++;
	}
}

void	draw_grid(t_game *g)
{
	t_pixel_point	p;

	for (p.y = 0; p.y < 10; p.y++) {
		for (p.x = 0; p.x < 10; p.x++) {
			if (map[p.y][p.x] == 0)
				paint_tile(&g->frame, p, 0xAAAAAA);
			else if (map[p.y][p.x] == 1)
				paint_tile(&g->frame, p, 0x000000);
			else if (map[p.y][p.x] == 2)
				paint_tile(&g->frame, p, 0xAA0500);
		}
	}
}

bool	is_in_bounds_of_window(t_pixel_point p)
{
	return !(p.x < 0 || p.x > (TILE_SIZE * 10) || p.y < 0
			|| p.y > (TILE_SIZE * 10));
}

bool	is_in_bounds_of_grid(t_vectori v)
{
	return !(v.x < 0 || v.x > 9 || v.y < 0 || v.y > 9 );
}

void	draw_square(t_img *frame, t_pixel_point pos, int size)
{
	int				y;
	int				x;
	t_pixel_point	point;
	
	y = 0;
	while (y <= size)
	{
		x = 0;
		if (y == 0 || y == size)
		{
			while (x <= size)
			{
				point.x = round((pos.x + x) - (double)size / 2);
				point.y = round((pos.y + y) - (double)size / 2);
				if (is_in_bounds_of_window(point))
						put_pixel_on_img(frame, point, 0x009F00);
				x++;
			}
		}
		point.x = round(pos.x - (double)size / 2);
		point.y = round((pos.y + y) - (double)size / 2);
		if (is_in_bounds_of_window(point))
			put_pixel_on_img(frame, point, 0x009F00);
		point.x = round(pos.x + (double)size / 2);
		point.y = round((pos.y + y) - (double)size / 2);
		if (is_in_bounds_of_window(point))
			put_pixel_on_img(frame, point, 0x009F00);
		y++;
	}
}

t_pixel_point	grid_coords_to_pixel_point(t_grid_coordsf v)
{
	return (t_vectori){.x = round(v.x * TILE_SIZE), .y = round(v.y * TILE_SIZE)};
}

t_grid_coordsf	pixel_point_to_grid_coord(t_pixel_point v)
{
	return (t_vectorf){.x = (double)v.x / TILE_SIZE, .y = (double)v.y / TILE_SIZE};
}

double	vector_len(t_vectorf v)
{
	return sqrt(v.y * v.y + v.x * v.x);
}

t_vectorf	vectorf_norm(t_vectorf v)
{
	const double	len = vector_len(v);
	if (len == 0)
		return v;
	return (t_vectorf){.x = v.x / len, .y = v.y / len};
}

t_vectorf	detect_walls(t_game *g, t_vectorf v)
{
	g->player.dir = vectorf_norm(vectorf_sub(v, g->player.pos));
	g->dp.delta.x = abs_f(1 / g->player.dir.x);
	g->dp.delta.y = abs_f(1 / g->player.dir.y);

	g->dp.inspected_grid = (t_grid_coordsi){.x = (int)g->player.pos.x, .y = (int)g->player.pos.y};
	if (g->player.dir.x < 0)
	{
		g->dp.ray_step.x = -1;
		g->dp.dist_until_first_side.x = (g->player.pos.x - g->dp.inspected_grid.x) * g->dp.delta.x;
	}
	else
	{
		g->dp.ray_step.x = 1;
		g->dp.dist_until_first_side.x = ((g->dp.inspected_grid.x + 1) - g->player.pos.x) * g->dp.delta.x;
	}
	if (g->player.dir.y < 0)
	{
		g->dp.ray_step.y = -1;
		g->dp.dist_until_first_side.y = (g->player.pos.y - g->dp.inspected_grid.y) * g->dp.delta.y;
	}
	else
	{
		g->dp.ray_step.y = 1;
		g->dp.dist_until_first_side.y = ((g->dp.inspected_grid.y + 1) - g->player.pos.y) * g->dp.delta.y;
	}

	g->dp.found_wall = false;
	double max_distance = 100;
	double distance = 0;
	while (!g->dp.found_wall && distance < max_distance)
	{
		// printf("difference: %f %f\n",vector_sub(v, g->player.pos).x, vector_sub(v, g->player.pos).y); 
		printf("ray delta: %f %f\n", g->dp.delta.x, g->dp.delta.y);
		printf("inspected grid: %d %d\n", g->dp.inspected_grid.x, g->dp.inspected_grid.x);
		if (g->dp.dist_until_first_side.x < g->dp.dist_until_first_side.y)
		{
			g->dp.inspected_grid.x += g->dp.ray_step.x;
			distance = g->dp.dist_until_first_side.x;
			g->dp.dist_until_first_side.x += g->dp.delta.x;
		}
		else
		{
			g->dp.inspected_grid.y += g->dp.ray_step.y;
			distance = g->dp.dist_until_first_side.y;
			g->dp.dist_until_first_side.y += g->dp.delta.y;
		}

		if (is_in_bounds_of_grid(g->dp.inspected_grid))
		{
			printf("is wall: %d\n", map[(int)g->dp.inspected_grid.y][(int)g->dp.inspected_grid.x] == 1);
			if (map[(int)g->dp.inspected_grid.y][(int)g->dp.inspected_grid.x] == 1)
				g->dp.found_wall = true;
		}
		else
			break;
	}

	t_vectorf	intersection;
	if (g->dp.found_wall)
		intersection = vectorf_add(g->player.pos, vectorf_scale(g->player.dir, distance));
	else
		intersection = v;
	return intersection;
}

int	move_line(t_game *g)
{
	int				x;
	int				y;
	t_grid_coordsf	line;

	mlx_mouse_get_pos(g->mlx, g->win, &x, &y);
	line = pixel_point_to_grid_coord((t_pixel_point){.x = x, .y = y});
	if (line.x > TILE_SIZE * 10)
		line.x = TILE_SIZE * 10;
	else if (line.x < 0)
		line.x = 0;
	if (line.y > TILE_SIZE * 10)
		line.y = TILE_SIZE * 10;
	else if (line.y < 0)
		line.y = 0;
	draw_grid(g);
	line = detect_walls(g, line);
	draw_line(&g->frame, grid_coords_to_pixel_point(g->player.pos), grid_coords_to_pixel_point(line));
	draw_square(&g->frame, grid_coords_to_pixel_point(line), 25);
	printf("x: %f\ty: %f\n", line.x, line.y);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	return 1;
}

int main()
{
	static t_game	g;

	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, 10 * TILE_SIZE, 10 * TILE_SIZE, "Test");
	g.frame.img = mlx_new_image(g.mlx, 10 * TILE_SIZE, 10 * TILE_SIZE);
	g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bits_per_pixel,
			&g.frame.line_len, &g.frame.endian);
	g.player.pos = (t_vectorf){.x = 2.5, .y = 1.5};
	mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);
	mlx_loop_hook(g.mlx, move_line, &g);
	mlx_loop(g.mlx);
}
