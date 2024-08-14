/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:26:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 16:18:17 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"

/* Gets color on certain point on the image. Checks for overflows */
unsigned int	get_pixel_of_img(t_img img, t_pixel_point p)
{
	if (p.x < 0 || p.x >= img.dimensions.x || p.y < 0
		|| p.y >= img.dimensions.y)
		return (0);
	return (*(unsigned int *)((img.addr + (p.y * img.line_len) + (p.x
					* img.bits_per_pixel / 8))));
}

/* Puts colored pixel on certain point on the image. Checks for overflows */
void	put_pixel_on_img(t_img *img, t_pixel_point p, int color)
{
	char	*dst;

	if (p.x < 0 || p.x >= img->dimensions.x || p.y < 0
		|| p.y >= img->dimensions.y)
		return ;
	dst = img->addr + (p.y * img->line_len + p.x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* Allocates new image and initializes parameters of its struct */
int	init_img_data(void *mlx, t_img *img, t_pixel_point p)
{
	img->dimensions = p;
	img->img = mlx_new_image(mlx, p.x, p.y);
	if (!img->img)
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	return (0);
}
