/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:15:32 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 19:19:44 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "cub3d.h"
/*////////////////////GRAPHICS\\\\\\\\\\\\\\\\\\\*/
/* Helful frocedures for displaying things on the screen, contains the main
 * rendering logic. */
typedef struct s_graphics
{
	int				draw_end;
	int				draw_start;
	int				line_height;
	double			wall_x_point;
	double			fog_percentage;
	t_pixel_point	tex_point;
	t_img			*texture;
}	t_graphics;

/*					// MINIMAP \\							*/
void			draw_minimap(t_game *g);

/*					// MLX IMG UTILS \\						*/
unsigned int	get_pixel_of_img(t_img img, t_pixel_point p);
unsigned int	get_pixel_of_img_bounds(t_img img, t_pixel_point p,
					t_pixel_point bounds);
void			put_pixel_on_img(t_img *img, t_pixel_point p, int color);
void			put_pixel_on_img_bounds(t_img *img, t_pixel_point p, int color,
					t_pixel_point bounds);

/*					// DRAW UTILS \\ 						*/
/* Functions for drawing simple shapes. */
void			draw_mininmap_line(t_img *frame, t_pixel_point start,
					t_pixel_point end, int color);
void			draw_square(t_img *frame, t_pixel_point pos, int size,
					int color);
void			draw_tile_bounds(t_img *frame, t_pixel_point p, int color,
					t_pixel_point bounds);
void			draw_transparent_tile(t_img *frame, t_pixel_point p, int color,
					t_pixel_point bounds);
void			draw_ceiling_and_floor(t_img *frame, int ceiling_color,
					int floor_color);

/*					// HANDS ANIMATION \\					*/
void	render_hands(t_game *g);

#endif
