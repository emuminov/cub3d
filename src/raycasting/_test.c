/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:16 by emuminov          #+#    #+#             */
/*   Updated: 2024/07/31 19:32:36 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TILE_SIZE 128

#include "../minilibx-linux/mlx.h"

const int map[10][10] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 2, 0, 0, 0, 0, 0, 0, 1 },
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

void	paint_img_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void paint_tile(void *mlx, void *win, int x, int y, int color)
{
	t_img	img;

	img.img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len,
			&img.endian);
	for (int y = 0; y < TILE_SIZE; y++) {
		for (int x = 0; x < TILE_SIZE; x++) {
			paint_img_pixel(&img, x, y, color);
		}
	}

	mlx_put_image_to_window(mlx, win, img.img, x * TILE_SIZE, y * TILE_SIZE);
	mlx_destroy_image(mlx, img.img);
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

void draw_line(t_vector start, t_vector end)
{
	t_vector	delta;
	double		slope;

	delta = vector_abs(vector_sub(end, start));
	slope = delta.y / delta.x;
	
}

int main()
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 10 * TILE_SIZE, 10 * TILE_SIZE, "Test");

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (map[y][x] == 0)
				paint_tile(mlx, win, x, y, 0xAAAAAA);
			else if (map[y][x] == 1)
				paint_tile(mlx, win, x, y, 0x000000);
			else if (map[y][x] == 2)
				paint_tile(mlx, win, x, y, 0xAA0500);
		}
	}

	mlx_loop(mlx);
}
