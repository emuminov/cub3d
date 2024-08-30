/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_int_conversions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:30:53 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/30 18:30:58 by emuminov         ###   ########.fr       */
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
