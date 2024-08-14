/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorf1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:33:40 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 15:16:44 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

/* This file and vectorf2.c contain functions that operate on vectorf */

double	vectorf_len(t_vectorf v)
{
	return (sqrt(v.y * v.y + v.x * v.x));
}

t_vectorf	vectorf_norm(t_vectorf v)
{
	const double	len = vectorf_len(v);

	if (len == 0)
		return (v);
	return ((t_vectorf){.x = v.x / len, .y = v.y / len});
}

t_vectorf	vectorf_sub(t_vectorf v1, t_vectorf v2)
{
	return ((t_vectorf){.x = v1.x - v2.x, .y = v1.y - v2.y});
}

t_vectorf	vectorf_dir(t_vectorf start, t_vectorf end)
{
	return (vectorf_norm(vectorf_sub(end, start)));
}

t_vectorf	vectorf_add(t_vectorf v1, t_vectorf v2)
{
	return ((t_vectorf){.x = v1.x + v2.x, .y = v1.y + v2.y});
}
