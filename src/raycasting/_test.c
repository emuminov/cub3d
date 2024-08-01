/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:16 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/01 19:35:08 by emuminov         ###   ########.fr       */
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
	y = y * TILE_SIZE;
	x = x * TILE_SIZE;
	while (y < y + TILE_SIZE)
	{
		while (x < x + TILE_SIZE)
		{
			put_pixel_on_img(frame, x, y, color);
			x++;
		}
		y++;
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
void	draw_line(void *mlx, void *win, t_vector start, t_vector end)
{
	const t_vector	delta = vector_sub(end, start);
	const int		steps = max(abs_d(delta.x), abs_d(delta.y));
	t_vector		inc;
	t_img			img;
	int				i;

	inc.x = delta.x / steps;
	inc.y = delta.y / steps;
	img.img = mlx_new_image(mlx, 10 * TILE_SIZE, 10 * TILE_SIZE);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len,
			&img.endian);

	i = 0;
	while (i < steps)
	{
		put_pixel_on_img(&img, round(start.x), round(start.y), 0x00A0FF);
		start.x += inc.x;
		start.y += inc.y;
		i++;
	}
	printf("%x\n", get_pixel_img(img, 0, 0));
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
}

int main()
{
	void	*mlx;
	void	*win;
	t_img	frame;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 10 * TILE_SIZE, 10 * TILE_SIZE, "Test");
	frame.img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_len, &frame.endian);

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (map[y][x] == 0)
				paint_tile(&frame, x, y, 0xAAAAAA);
			else if (map[y][x] == 1)
				paint_tile(&frame, x, y, 0x000000);
			else if (map[y][x] == 2)
				paint_tile(&frame, x, y, 0xAA0500);
		}
	}

	mlx_put_image_to_window(mlx, win, frame.img, 0, 0);
	// draw_line(mlx, win, (t_vector){.x = TILE_SIZE * 0.25, .y = TILE_SIZE * 0.25}, (t_vector){.x = TILE_SIZE * 0.10, .y = TILE_SIZE * 0.25});

	mlx_loop(mlx);
}
