/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:20:22 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/26 18:24:09 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_LOGIC_H
# define GAME_LOGIC_H
# include "cub3d.h"
/*					// MLX IMG UTILS \\		 				*/
int		init_img_data(void *mlx, t_img *img, t_pixel_point p);
int		resize_image(t_game *g, t_img *old, int new_width, int new_height);

/*					// CONTROLS HANDLING \\ 				*/
bool				is_move_key_pressed(t_game *g);
int					handle_key_press(int keysym, t_game *g);
int					handle_key_release(int keysym, t_game *g);
t_vectorf			mouse_pos_to_grid_coordsf(t_game *g);

/*					// INIT GAME \\ 						*/
/* Initializes mlx, creates new window, initializes game struct */
int					_old_start_mlx(t_game *g, int x, int y);


/*					// MOVEMENT \\							*/
t_grid_coordsf		move_player(t_player p, const t_controls *controls);
t_vectorf			get_movement_dir(const t_controls *controls,
						const t_player *player);
void				resolve_rotation(t_game *g);
void				resolve_movement(t_game *g);

/*					// EXIT \\								*/
int					exit_game(t_game *g);

/*					// ULDATE GAME STATE \\					*/
/* Everything that updates the state during runtime. For now it's a simple
 * function that includes resolution of movement and rotations. */
void				update_game_state(t_game *g);


/*					// MOUSE \\								*/
/* Handles rotations with mouse. */
void				handle_mouse(t_game *g);

/*					// DOORS \\				*/
void				toggle_door(t_game *g);
#endif
