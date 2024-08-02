/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:16 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/02 18:25:46 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
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

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_dda_params
{
	t_vector	inspected_grid;
	t_vector	ray_step;
	t_vector	delta;
	t_vector	dist_until_first_side;
	double		camera;
}				t_dda_params;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}				t_player;

typedef struct	s_game
{
	void			*mlx;
	void			*win;
	t_img			frame;
	t_player		player;
	t_dda_params	dp;
}				t_game;

void	put_pixel_on_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void paint_tile(t_img *frame, int x, int y, int color)
{
	t_vector	start;
	t_vector	end;

	start.y = y * TILE_SIZE;
	start.x = x * TILE_SIZE;

	end.y = start.y + TILE_SIZE;
	end.x = start.x + TILE_SIZE;
	while (start.y < end.y)
	{
		start.x = x * TILE_SIZE;
		while (start.x < end.x)
		{
			put_pixel_on_img(frame, start.x, start.y, color);
			start.x++;
		}
		start.y++;
	}
}

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	return (t_vector){.x=v1.x - v2.x, .y=v1.y - v2.y};
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	return (t_vector){.x=v1.x + v2.x, .y=v1.y + v2.y};
}

t_vector	vector_scale(t_vector v, double nbr)
{
	return (t_vector){.x=v.x * nbr, .y=v.y * nbr};
}

t_vector	vector_abs(t_vector v)
{
	t_vector res;

	if (v.x < 0)
		res.x = -v.x;
	if (v.y < 0)
		res.y = -v.y;
	return res;
}

double	abs_d(double n)
{
	if (n < 0)
		return -n;
	return n;
}

double	vector_find_slope(t_vector delta)
{
	if (delta.x == 0)
		return INFINITY;
	return delta.y / delta.x;
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
void	draw_line(t_img *frame, t_vector start, t_vector end)
{
	const t_vector	delta = vector_sub(end, start);
	const int		steps = max(abs_d(delta.x), abs_d(delta.y));
	t_vector		inc;
	int				i;

	inc.x = delta.x / steps;
	inc.y = delta.y / steps;

	i = 0;
	while (i < steps)
	{
		put_pixel_on_img(frame, round(start.x), round(start.y), 0x00A0FF);
		start.x += inc.x;
		start.y += inc.y;
		i++;
	}
}

void	draw_grid(t_game *g)
{
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (map[y][x] == 0)
				paint_tile(&g->frame, x, y, 0xAAAAAA);
			else if (map[y][x] == 1)
				paint_tile(&g->frame, x, y, 0x000000);
			else if (map[y][x] == 2)
				paint_tile(&g->frame, x, y, 0xAA0500);
		}
	}
}

bool	is_in_bounds_of_window(t_vector v)
{
	return !(v.x < 0 || v.x > (TILE_SIZE * 10) || v.y < 0
			|| v.y > (TILE_SIZE * 10));
}

bool	is_in_bounds_of_grid(t_vector v)
{
	return !(v.x < 0 || v.x > 9 || v.y < 0 || v.y > 9 );
}

void	draw_square(t_img *frame, t_vector pos, int size)
{
	int			y;
	int			x;
	t_vector	point;
	
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
						put_pixel_on_img(frame, point.x, point.y, 0x009F00);
				x++;
			}
		}
		point.x = round(pos.x - (double)size / 2);
		point.y = round((pos.y + y) - (double)size / 2);
		if (is_in_bounds_of_window(point))
			put_pixel_on_img(frame, point.x, point.y, 0x009F00);
		point.x = round(pos.x + (double)size / 2);
		point.y = round((pos.y + y) - (double)size / 2);
		if (is_in_bounds_of_window(point))
			put_pixel_on_img(frame, point.x, point.y, 0x009F00);
		y++;
	}
}

t_vector	grid_coords_to_pixel_point(t_vector v)
{
	return (t_vector){.x = TILE_SIZE * v.x, .y = TILE_SIZE * v.y};
}

t_vector	pixel_point_to_grid_coord(t_vector v)
{
	return (t_vector){.x = v.x / TILE_SIZE, .y = v.y / TILE_SIZE};
}

double	vector_len(t_vector v)
{
	return sqrt(v.y * v.y + v.x * v.x);
}

t_vector	vector_norm(t_vector v)
{
	const double	len = vector_len(v);
	if (len == 0)
		return v;
	return (t_vector){.x = v.x / len, .y = v.y / len};
}

double	abs_f(double nbr)
{
	if (nbr < 0)
		return -nbr;
	return nbr;
}

t_vector	detect_walls(t_game *g, t_vector v)
{
	g->player.dir = vector_norm(vector_sub(v, g->player.pos));
	// g->dp.delta.x = sqrt(1 + (g->player.dir.y * g->player.dir.y) / (g->player.dir.x * g->player.dir.x));
	// g->dp.delta.y = sqrt(1 + (g->player.dir.x * g->player.dir.x) / (g->player.dir.y * g->player.dir.y));
	g->dp.delta.x = abs_f(1 / g->player.dir.x);
	g->dp.delta.y = abs_f(1 / g->player.dir.y);

	// TODO: inspected grid should be int
	g->dp.inspected_grid = (t_vector){.x = floor(g->player.pos.x), .y = floor(g->player.pos.y)};
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

	bool found_wall = false;
	double max_distance = 100;
	double distance = 0;
	while (!found_wall && distance < max_distance)
	{
		// printf("difference: %f %f\n",vector_sub(v, g->player.pos).x, vector_sub(v, g->player.pos).y); 
		printf("ray delta: %f %f\n", g->dp.delta.x, g->dp.delta.y);
		printf("inspected grid: %f %f\n", g->dp.inspected_grid.x, g->dp.inspected_grid.x);
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
			{
				found_wall = true;
			}
		}
		else
		{
			break;
		}
	}

	t_vector	intersection;
	if (found_wall)
	{
		intersection = vector_add(g->player.pos, vector_scale(g->player.dir, distance));
	}
	else
		intersection = v;
	return intersection;
}

int	move_line(t_game *g)
{
	int			x;
	int			y;
	t_vector	line;

	mlx_mouse_get_pos(g->mlx, g->win, &x, &y);
	line = (t_vector){.x = x, .y = y};
	if (line.x > TILE_SIZE * 10)
		line.x = TILE_SIZE * 10;
	else if (line.x < 0)
		line.x = 0;
	if (line.y > TILE_SIZE * 10)
		line.y = TILE_SIZE * 10;
	else if (line.y < 0)
		line.y = 0;
	draw_grid(g);
	line = detect_walls(g, pixel_point_to_grid_coord(line));
	// line = pixel_point_to_grid_coord(line);
	draw_line(&g->frame, grid_coords_to_pixel_point(g->player.pos), grid_coords_to_pixel_point(line));
	draw_square(&g->frame, grid_coords_to_pixel_point(line), 25);
	printf("x: %f\ty: %f\n", line.x, line.y);
	// printf("x: %f\ty: %f\n", pixel_point_to_grid_coord(line).x, pixel_point_to_grid_coord(line).y);
	// draw_line(&g->frame, grid_coords_to_pixel_point(g->player.pos), grid_coords_to_pixel_point(line));
	// draw_square(&g->frame, grid_coords_to_pixel_point(line), 25);
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
	g.player.pos = (t_vector){.x = 2.5, .y = 1.5};
	mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);
	mlx_loop_hook(g.mlx, move_line, &g);
	mlx_loop(g.mlx);
}
