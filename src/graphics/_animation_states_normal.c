/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_states_normal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:53:33 by eandre            #+#    #+#             */
/*   Updated: 2024/09/02 19:54:33 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/constants.h"
#include "../../include/graphics.h"
#include "../../include/cub3d.h"

void	render_idle(t_game *g, int *walk_f, int *idle_f, int *frame)
{
	*walk_f = 0;
	render_animation(g, *idle_f, g->idle_textures);
	if (!(*frame % 10))
		(*idle_f)++;
	if (*idle_f == IDLE_LAST)
		*idle_f = 0;
}

void	render_walk(t_game *g, int *walk_f, int *idle_f, int *frame)
{
	*idle_f = 0;
	render_animation(g, *walk_f, g->walk_textures);
	if (!(*frame % 5))
		(*walk_f)++;
	if (*walk_f == WALK_LAST)
		*walk_f = 0;
}
