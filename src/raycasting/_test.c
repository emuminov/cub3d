/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:16 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/01 20:27:11 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#define TILE_SIZE 128

#include "../minilibx-linux/mlx.h"

const int map[10][10] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 2, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
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

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_img	frame;
}				t_game;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

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

t_vector vector_sub(t_vector v1, t_vector v2)
{
	return (t_vector){.x=v1.x - v2.x, .y=v1.y - v2.y};
}

t_vector vector_abs(t_vector v)
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

int	move_line(t_game *g)
{
	int			x;
	int			y;
	t_vector	line;

	mlx_mouse_get_pos(g->mlx, g->win, &x, &y);
	line = (t_vector){.x = x, .y = y};
	printf("x: %f\ty: %f\n", line.x, line.y);
	draw_grid(g);
	draw_line(&g->frame, (t_vector){.x = TILE_SIZE * 2.5, .y = TILE_SIZE * 1.5}, line);
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

	mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);
	mlx_loop_hook(g.mlx, move_line, &g);
	mlx_loop(g.mlx);
}
