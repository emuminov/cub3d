/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorf2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:15:40 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 15:55:30 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

t_vectorf	vectorf_scale(t_vectorf v, double nbr)
{
	return ((t_vectorf){.x = v.x * nbr, .y = v.y * nbr});
}

t_vectorf	vectorf_abs(t_vectorf v)
{
	return ((t_vectorf){.x = abs_f(v.x), .y = abs_f(v.y)});
}

// TODO: store the rotation constants somewhere
t_vectorf	vectorf_rotate(t_vectorf dir, double theta)
{
	t_vectorf	res;

	theta = theta * RADIAN_TO_DEGREE_SCALING;
	res.x = dir.x * cos(theta) - dir.y * sin(theta);
	res.y = dir.x * sin(theta) + dir.y * cos(theta);
	return (res);
}

t_vectorf	vectorf_round(t_vectorf v)
{
	return ((t_vectorf){.x = round(v.x), .y = round(v.y)});
}

t_vectorf	vectorf_epsilon(t_vectorf dir)
{
	return ((t_vectorf){.x = 1e-6 * sign_f(dir.x), .y = 1e-6 * sign_f(dir.y)});
}
