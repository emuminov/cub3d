/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:15:32 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 02:08:10 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "cub3d.h"
/*					// MINIMAP \\							*/
void				draw_minimap(t_game *g);

/*					// MLX IMG UTILS \\						*/
unsigned int		get_pixel_of_img(t_img img, t_pixel_point p);
void				put_pixel_on_img(t_img *img, t_pixel_point p,
		int color);
void				put_pixel_on_img_bounds(t_img *img, t_pixel_point p,
		int color, t_pixel_point bounds);

/*					// DRAW UTILS \\ 						*/
/* Functions for drawing simple shapes. */
void				draw_line(t_img *frame, t_pixel_point start,
						t_pixel_point end, int color);
void				draw_hollow_square(t_img *frame, t_pixel_point pos,
						int size, int color);
void				draw_square(t_img *frame, t_pixel_point pos, int size,
						int color);
void				draw_tile_bounds(t_img *frame, t_pixel_point p, int color,
		int tile_size, t_pixel_point bounds);
void				draw_ceiling_and_floor(t_img *frame, int ceiling_color,
		int floor_color);
#endif
