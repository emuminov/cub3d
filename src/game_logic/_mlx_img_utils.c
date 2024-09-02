/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mlx_img_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:44:21 by eandre            #+#    #+#             */
/*   Updated: 2024/09/02 16:19:57 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/game_logic.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>

static void	nxt_ft_size(t_img *n_bg, t_img *o_bg, int y);

/* Allocates new image and initializes parameters of its struct */
int	init_img_data(void *mlx, t_img *img, t_pixel_point p)
{
	img->dimensions = p;
	img->img = mlx_new_image(mlx, p.x, p.y);
	if (!img->img)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	return (0);
}

int	init_texture(t_game *g, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(g->mlx,
			path,
			&texture->dimensions.x,
			&texture->dimensions.y);
	if (texture->img == NULL)
		return (1);
	if (resize_image(g, texture, g->window_size.x, g->window_size.y) == 1)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_len,
			&texture->endian);
	return (0);
}


bool textures_are_valid(t_img *textures, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!textures[i].img)
			return (false);
		i++;
	}
	return (true);
}


int	resize_image(t_game *g, t_img *old, int new_width, int new_height)
{
	t_img	*new;
	void	*new_img;

	new = ft_calloc(1, sizeof(t_img));
	if (!new)
		return (1);
	new->dimensions.x = new_width;
	new->dimensions.y = new_height;
	old->addr = mlx_get_data_addr(old->img, &(old->bits_per_pixel),
			&(old->line_len), &(old->endian));
	new_img = mlx_new_image(g->mlx, new_width, new_height);
	if (!new_img)
	{
		free(new);
		return (1);
	}
	new->addr = mlx_get_data_addr(new_img, &(new->bits_per_pixel),
			&(new->line_len), &(new->endian));
	nxt_ft_size(new, old, 0);
	mlx_destroy_image(g->mlx, old->img);
	old->img = new_img;
	old->dimensions.x = new_width;
	old->dimensions.y = new_height;
	free(new);
	return (0);
}

static void	nxt_ft_size(t_img *n_bg, t_img *o_bg, int y)
{
	int	x;
	int	k;
	int	og_x;
	int	og_y;

	while (y < n_bg->dimensions.y)
	{
		x = 0;
		while (x < n_bg->dimensions.x)
		{
			og_x = (x * o_bg->dimensions.x) / n_bg->dimensions.x;
			og_y = (y * o_bg->dimensions.y) / n_bg->dimensions.y;
			k = 0;
			while (k < n_bg->bits_per_pixel / 8)
			{
				n_bg->addr[y * n_bg->line_len + x * (n_bg->bits_per_pixel / 8)
					+ k] = o_bg->addr[og_y * o_bg->line_len + og_x
					* (o_bg->bits_per_pixel / 8) + k];
				k++;
			}
			x++;
		}
		y++;
	}
}
