/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _hands_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:38:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/27 18:40:40 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/constants.h"
#include "../../include/cub3d.h"

// void	render_hands(t_game *g)
// {
// 	static int	punch_frame;
// 	static int	idle_frame;
//
// 	if (g->player.should_punch)
// 	{
// 		render_punch_animation(g->punch_textures[punch_frame]);
// 		punch_frame++;
// 		if (punch_frame == LAST_PUNCH_FRAME)
// 		{
// 			idle_frame = 0;
// 			punch_frame = 0;
// 			g->player.should_punch = false;
// 		}
// 	}
// 	else
// 	{
// 		render_idle_animation(g->idle_textures[idle_frame]);
// 		idle_frame++;
// 		if (punch_frame == LAST_IDLE_FRAME)
// 			idle_frame = 0;
// 	}
// }
