/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectori.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:03 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 14:52:48 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vectori	vectori_sub(t_vectori v1, t_vectori v2)
{
	return ((t_vectori){.x = v1.x - v2.x, .y = v1.y - v2.y});
}
