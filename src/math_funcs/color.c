/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:00:26 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/30 17:47:06 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
int	get_r(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	get_g(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/* Mixes two colors, percentage denotes the percentage of the first color in the
 * result. For example, percentage == 80 means that there is 80% of rgb1 and
 * 20% of rgb2. */
int	mix_rgb(int rgb1, int rgb2, double percentage)
{
	double	percentage2;
	int		res;

	percentage2 = 1.0 - percentage;
	res = rgb_to_int(
		(get_r(rgb1) * percentage + get_r(rgb2) * percentage2),
		(get_g(rgb1) * percentage + get_g(rgb2) * percentage2), 
		(get_b(rgb1) * percentage + get_b(rgb2) * percentage2)
	);
	return (res);
}

int	get_transparent_color(int transparency, int color, int background)
{
	double	alpha;
	double	oneminusalpha;

	alpha = (double)transparency / 255;
	oneminusalpha = 1 - alpha;

	return rgb_to_int(
		(get_r(color) * alpha) + (oneminusalpha * get_r(background)),
		(get_g(color) * alpha) + (oneminusalpha * get_g(background)),
		(get_b(color) * alpha) + (oneminusalpha * get_b(background))
	);
}
