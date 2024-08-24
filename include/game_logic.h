/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:20:22 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 00:20:53 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GAME_LOGIC_H
# define GAME_LOGIC_H
# include "cub3d.h"
int		init_img_data(void *mlx, t_img *img, t_pixel_point p);
int		resize_image(t_game *g, t_img *old, int new_width, int new_height);
#endif
