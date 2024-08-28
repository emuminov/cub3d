/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:37:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/28 18:46:58 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H
# define WINDOW_WIDTH 896
# define WINDOW_HEIGHT 768
# define MINIMAP_SIZE 320
# define MINIMAP_TILE_SIZE 64
# define TILE_SIZE 128
# define RADIAN_TO_DEGREE_SCALING 0.0174533
# define MOVEMENT_SPEED 0.08
# define ROTATION_SPEED 4.0
# define MOUSE_ROTATION_SPEED 1.0
# define PLAYER_SIZE 0.1
# define MINIMAP_ALPHA 200
# define MINIMAP_FOV_ALPHA 5
# define LAST_PUNCH_FRAME 10
# define LAST_IDLE_FRAME 10
# ifdef HIDE_MOUSE
#  define SHOULD_HIDE_MOUSE 1
# else 
#  define SHOULD_HIDE_MOUSE 0
# endif
#endif
