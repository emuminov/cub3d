/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:00:26 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/23 22:16:05 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	get_transparent_color(int transparency, int color, int background)
{
	double	alpha;
	double	oneminusalpha;

	alpha = (double)transparency / 255;
	oneminusalpha = 1 - alpha;

	return (rgb_to_int(
		(get_r(color) * alpha) + (oneminusalpha * get_r(background)),
		(get_g(color) * alpha) + (oneminusalpha * get_g(background)),
		(get_b(color) * alpha) + (oneminusalpha * get_b(background))
	));
}
