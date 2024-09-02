/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectori.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:03 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 15:55:35 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vectori	vectori_sub(t_vectori v1, t_vectori v2)
{
	return ((t_vectori){.x = v1.x - v2.x, .y = v1.y - v2.y});
}

t_vectori	vectori_add(t_vectori v1, t_vectori v2)
{
	return ((t_vectori){.x = v1.x + v2.x, .y = v1.y + v2.y});
}

t_vectori	vectorf_to_vectori(t_vectorf v)
{
	return ((t_vectori){.x = (int)v.x, .y = (int)v.y});
}

t_vectori	vectori(int x, int y)
{
	return ((t_vectori){.x = x, .y = y});
}
