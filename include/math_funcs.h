/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_funcs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:25:47 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/25 00:34:59 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FUNCS_H
# define MATH_FUNCS_H
# include "cub3d.h"

/*////////////////////MATH FUNCS\\\\\\\\\\\\\\\\\\\*/
/* Used for pure calculations with no side effects. Operate on ints, doubles and
 * vectors that represent direction, grid coordinates, pixels on window. */
/*                  // VECTORF \\ 							*/
double				vectorf_len(t_vectorf v);
t_vectorf			vectorf_norm(t_vectorf v);
t_vectorf			vectorf_sub(t_vectorf v1, t_vectorf v2);
t_vectorf			vectorf_add(t_vectorf v1, t_vectorf v2);
t_vectorf			vectorf_dir(t_vectorf start, t_vectorf end);
t_vectorf			vectorf_scale(t_vectorf v, double nbr);
t_vectorf			vectorf_abs(t_vectorf v);
t_vectorf			vectorf_rotate(t_vectorf dir, double theta);
t_vectorf			vectorf_round(t_vectorf v);
t_vectorf			vectorf_epsilon(t_vectorf dir);

/*					// GRID PIXEL CONVERSIONS \\ 			*/
t_pixel_point		grid_coordsf_to_pixel_point(t_grid_coordsf v);
t_pixel_point		grid_coordsi_to_pixel_point(t_grid_coordsi v);
t_grid_coordsf		pixel_point_to_grid_coordsf(t_pixel_point v);
t_grid_coordsi		pixel_point_to_grid_coordsi(t_pixel_point v);

/*					// GRID BOUNDS CHECKING \\ 				*/
bool				is_in_bounds_of_grid(t_grid_coordsi v,
						t_grid_coordsi map_size);
bool				is_beyond(t_grid_coordsf v1, t_grid_coordsf v2,
						t_vectorf dir);

/* 					// VECTORI \\ 							*/
t_vectori			vectori_sub(t_vectori v1, t_vectori v2);
t_vectori			vectori_add(t_vectori v1, t_vectori v2);

/*					// UTILS \\  							*/
double				abs_f(double n);
double				sign_f(double nbr);
int					max(int n1, int n2);
int					normalize(int value, int min, int max);

/*					// COLOR \\  							*/
int					rgb_to_int(int r, int g, int b);
int					get_r(int rgb);
int					get_g(int rgb);
int					get_b(int rgb);
int					get_transparent_color(int transparency, int color,
		int background);
#endif
