/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:16 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/12 19:22:08 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#define TILE_SIZE 128
#define RADIAN_TO_DEGREE_SCALING 0.0174533

enum			e_direction
{
	up,
	down,
	left,
	right
};

t_pixel_point	grid_coordsf_to_pixel_point(t_grid_coordsf v)
{
	return ((t_pixel_point){.x = round(v.x * TILE_SIZE), .y = round(v.y
			* TILE_SIZE)});
}

t_pixel_point	grid_coordsi_to_pixel_point(t_grid_coordsi v)
{
	return ((t_pixel_point){.x = v.x * TILE_SIZE, .y = v.y * TILE_SIZE});
}

t_grid_coordsf	pixel_point_to_grid_coordsf(t_pixel_point v)
{
	return ((t_grid_coordsf){.x = (double)v.x / TILE_SIZE, .y = (double)v.y
		/ TILE_SIZE});
}

t_grid_coordsi	pixel_point_to_grid_coordsi(t_pixel_point v)
{
	return ((t_grid_coordsi){.x = v.x / TILE_SIZE, .y = v.y / TILE_SIZE});
}

double	vectorf_len(t_vectorf v)
{
	return (sqrt(v.y * v.y + v.x * v.x));
}

t_vectorf	vectorf_norm(t_vectorf v)
{
	const double	len = vectorf_len(v);

	if (len == 0)
		return (v);
	return ((t_vectorf){.x = v.x / len, .y = v.y / len});
}

t_vectorf	vectorf_sub(t_vectorf v1, t_vectorf v2)
{
	return ((t_vectorf){.x = v1.x - v2.x, .y = v1.y - v2.y});
}

t_vectorf	vectorf_dir(t_vectorf start, t_vectorf end)
{
	return (vectorf_norm(vectorf_sub(end, start)));
}

t_vectorf	vectorf_add(t_vectorf v1, t_vectorf v2)
{
	return ((t_vectorf){.x = v1.x + v2.x, .y = v1.y + v2.y});
}

t_vectorf	vectorf_scale(t_vectorf v, double nbr)
{
	return ((t_vectorf){.x = v.x * nbr, .y = v.y * nbr});
}

t_vectori	vectori_sub(t_vectori v1, t_vectori v2)
{
	return ((t_vectori){.x = v1.x - v2.x, .y = v1.y - v2.y});
}

double	abs_f(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

t_vectorf	vectorf_abs(t_vectorf v)
{
	return ((t_vectorf){.x = abs_f(v.x), .y = abs_f(v.y)});
}

// TODO: store the rotation constants somewhere
t_vectorf	vectorf_rotate(t_vectorf dir, double theta)
{
	t_vectorf	res;

	theta = theta * RADIAN_TO_DEGREE_SCALING;
	res.x = dir.x * cos(theta) - dir.y * sin(theta);
	res.y = dir.x * sin(theta) + dir.y * cos(theta);
	return (res);
}

int	max(int n1, int n2)
{
	if (n1 >= n2)
		return n1;
	return n2;
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len) + (x
					* img.bits_per_pixel / 8))));
}

const int		map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 2, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void	put_pixel_on_img(t_img *img, t_pixel_point p, int color)
{
	char	*dst;

	if (p.x < 0 || p.x >= img->dimensions.x || p.y < 0
		|| p.y >= img->dimensions.y)
		return ;
	dst = img->addr + (p.y * img->line_len + p.x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	paint_tile(t_img *frame, t_grid_coordsi p, int color)
{
	t_pixel_point	start;
	t_pixel_point	end;

	start = grid_coordsi_to_pixel_point(p);
	end.y = start.y + TILE_SIZE;
	end.x = start.x + TILE_SIZE;
	while (start.y < end.y)
	{
		start.x = p.x * TILE_SIZE;
		while (start.x < end.x)
		{
			put_pixel_on_img(frame, start, color);
			start.x++;
		}
		start.y++;
	}
}

/* DDA line drawing algorithm */
void	draw_line(t_img *frame, t_pixel_point start, t_pixel_point end)
{
	const t_pixel_point	delta = vectori_sub(end, start);
	const int			steps = max(abs(delta.x), abs(delta.y));
	t_vectorf			next_point;
	t_vectorf			inc;
	int					i;

	next_point = (t_vectorf){.x = start.x, .y = start.y};
	inc = (t_vectorf){.x = (double)delta.x / steps, .y = (double)delta.y
		/ steps};
	i = 0;
	while (i < steps)
	{
		put_pixel_on_img(frame, (t_pixel_point){.x = round(next_point.x),
			.y = round(next_point.y)}, 0x1010FF);
		next_point.x += inc.x;
		next_point.y += inc.y;
		i++;
	}
}

void	draw_grid(t_game *g)
{
	t_grid_coordsi			p;
	const t_grid_coordsi	visible_grid = pixel_point_to_grid_coordsi(g->frame.dimensions);

	p.y = 0;
	while (p.y < visible_grid.y)
	{
		p.x = 0;
		while (p.x < visible_grid.x)
		{
			if (map[p.y][p.x] == 0 || map[p.y][p.x] == 2)
				paint_tile(&g->frame, p, 0xAAAAAA);
			else if (map[p.y][p.x] == 1)
				paint_tile(&g->frame, p, 0x454545);
			p.x++;
		}
		p.y++;
	}
}

bool	is_in_bounds_of_grid(t_grid_coordsi v)
{
	return !(v.x < 0 || v.x > 9 || v.y < 0 || v.y > 9);
}

void	draw_hollow_square(t_img *frame, t_pixel_point pos, int size)
{
	int				i;
	t_pixel_point	point;

	i = 0;
	while (i <= size)
	{
		point.x = round((pos.x + i) - (double)size / 2);
		point.y = round((pos.y) - (double)size / 2);
		put_pixel_on_img(frame, point, 0x009F00);
		point.x = round((pos.x) - (double)size / 2);
		point.y = round((pos.y + i) - (double)size / 2);
		put_pixel_on_img(frame, point, 0x009F00);
		point.x = round((pos.x + size) - (double)size / 2);
		point.y = round((pos.y + i) - (double)size / 2);
		put_pixel_on_img(frame, point, 0x009F00);
		point.x = round((pos.x + i) - (double)size / 2);
		point.y = round((pos.y + size) - (double)size / 2);
		put_pixel_on_img(frame, point, 0x009F00);
		i++;
	}
}

void	draw_square(t_img *frame, t_pixel_point pos, int size)
{
	t_pixel_point	point;
	int				y;
	int				x;

	y = 0;
	while (y <= size)
	{
		x = 0;
		while (x <= size)
		{
			point.x = round((pos.x + x) - (double)size / 2);
			point.y = round((pos.y + y) - (double)size / 2);
			put_pixel_on_img(frame, point, 0x5F009F);
			x++;
		}
		y++;
	}
}

double	signf(double nbr)
{
	if (nbr < 0)
		return -1;
	return 1;
}

void	set_initial_dda_params(t_dda_params *dp, t_grid_coordsf start,
		t_vectorf dir, double max_distance)
{
	dp->rate_of_change.x = abs_f(1 / dir.x);
	dp->rate_of_change.y = abs_f(1 / dir.y);
	dp->inspected_grid = (t_grid_coordsi){.x = (int)start.x, .y = start.y};
	dp->ray_step.x = signf(dir.x);
	dp->ray_step.y = signf(dir.y);
	if (dir.x < 0)
		dp->dist_until_grid_side.x = (start.x - dp->inspected_grid.x)
			* dp->rate_of_change.x;
	else
		dp->dist_until_grid_side.x = ((dp->inspected_grid.x + 1) - start.x)
			* dp->rate_of_change.x;
	if (dir.y < 0)
		dp->dist_until_grid_side.y = (start.y - dp->inspected_grid.y)
			* dp->rate_of_change.y;
	else
		dp->dist_until_grid_side.y = ((dp->inspected_grid.y + 1) - start.y)
			* dp->rate_of_change.y;
	dp->found_wall = false;
	dp->max_distance = max_distance;
	dp->distance = 0;
}

void	check_next_grid_cell(t_dda_params *dp)
{
	if (dp->dist_until_grid_side.x < dp->dist_until_grid_side.y)
	{
		dp->inspected_grid.x += dp->ray_step.x;
		dp->distance = dp->dist_until_grid_side.x;
		dp->dist_until_grid_side.x += dp->rate_of_change.x;
	}
	else
	{
		dp->inspected_grid.y += dp->ray_step.y;
		dp->distance = dp->dist_until_grid_side.y;
		dp->dist_until_grid_side.y += dp->rate_of_change.y;
	}
}

t_vectorf	check_wall_in_dir(t_dda_params *dp, t_grid_coordsf start,
		t_vectorf dir, double max_distance)
{
	t_vectorf	intersection;

	set_initial_dda_params(dp, start, dir, max_distance);
	while (!dp->found_wall && dp->distance < dp->max_distance)
	{
		check_next_grid_cell(dp);
		if (is_in_bounds_of_grid(dp->inspected_grid))
		{
			if (map[(int)dp->inspected_grid.y][(int)dp->inspected_grid.x] == 1)
				dp->found_wall = true;
		}
		else
			break ;
	}
	if (dp->found_wall)
		intersection = vectorf_add(start, vectorf_scale(dir, dp->distance));
	else
		intersection = (t_grid_coordsf){.x = -1, .y = -1};
	return intersection;
}

int	handle_key_press(int keysym, t_game *g)
{
	if (keysym == XK_Left)
		g->controls.rotate_left_pressed = true;
	else if (keysym == XK_Right)
		g->controls.rotate_right_pressed = true;
	else if (keysym == XK_w)
		g->controls.move_up_pressed = true;
	else if (keysym == XK_s)
		g->controls.move_down_pressed = true;
	else if (keysym == XK_a)
		g->controls.move_left_pressed = true;
	else if (keysym == XK_d)
		g->controls.move_right_pressed = true;
	return (0);
}

int	handle_key_release(int keysym, t_game *g)
{
	if (keysym == XK_Left)
		g->controls.rotate_left_pressed = false;
	else if (keysym == XK_Right)
		g->controls.rotate_right_pressed = false;
	else if (keysym == XK_w)
		g->controls.move_up_pressed = false;
	else if (keysym == XK_s)
		g->controls.move_down_pressed = false;
	else if (keysym == XK_a)
		g->controls.move_left_pressed = false;
	else if (keysym == XK_d)
		g->controls.move_right_pressed = false;
	return (0);
}

t_vectorf	mouse_pos_to_grid_coordsf(t_game *g)
{
	int				x;
	int				y;
	t_grid_coordsf	mouse_grid_pos;

	mlx_mouse_get_pos(g->mlx, g->win, &x, &y);
	mouse_grid_pos = pixel_point_to_grid_coordsf((t_pixel_point){.x = x,
			.y = y});
	if (mouse_grid_pos.x > g->window_size.x)
		mouse_grid_pos.x = g->window_size.x;
	else if (mouse_grid_pos.x < 0)
		mouse_grid_pos.x = 0;
	if (mouse_grid_pos.y > g->window_size.y)
		mouse_grid_pos.y = g->window_size.y;
	else if (mouse_grid_pos.y < 0)
		mouse_grid_pos.y = 0;
	return mouse_grid_pos;
}

t_vectorf	vectorf_epsilon(t_vectorf dir)
{
	return (t_vectorf){.x = 1e-9 * signf(dir.x), .y = 1e-9 * signf(dir.y)};
}

t_grid_coordsf	move_player(t_player p, const t_controls *controls)
{
	if (controls->move_up_pressed)
		p.pos = vectorf_add(p.pos, vectorf_scale(p.dir, 0.1));
	else if (controls->move_down_pressed)
		p.pos = vectorf_sub(p.pos, vectorf_scale(p.dir, 0.1));
	else if (controls->move_left_pressed)
		p.pos = vectorf_add(p.pos, vectorf_scale(vectorf_rotate(p.dir, -90),
					0.1));
	else if (controls->move_right_pressed)
		p.pos = vectorf_add(p.pos, vectorf_scale(vectorf_rotate(p.dir, 90),
					0.1));
	return p.pos;
}

/* Checks if v1 goes further than v2 in the direction dir */
bool	is_beyond(t_grid_coordsf v1, t_grid_coordsf v2, t_vectorf dir)
{
	if (dir.x < 0 && dir.y >= 0)
		return (v1.x <= v2.x || v1.y >= v2.y);
	if (dir.x < 0 && dir.y < 0)
		return (v1.x <= v2.x || v1.y <= v2.y);
	if (dir.x >= 0 && dir.y >= 0)
		return (v1.x >= v2.x || v1.y >= v2.y);
	if (dir.x >= 0 && dir.y < 0)
		return (v1.x >= v2.x || v1.y <= v2.y);
	return 1;
}

/* Gets the direction of player based on the key pressed */
t_vectorf	get_movement_dir(const t_controls *controls, const t_player *player)
{
	t_vectorf	dir;

	dir = (t_vectorf){.x = -1, .y = -1};
	if (controls->move_up_pressed)
		dir = player->dir;
	else if (controls->move_down_pressed)
		dir = vectorf_rotate(player->dir, 180);
	else if (controls->move_left_pressed)
		dir = vectorf_rotate(player->dir, -90);
	else if (controls->move_right_pressed)
		dir = vectorf_rotate(player->dir, 90);
	return dir;
}

void	resolve_rotation(t_game *g)
{
	if (g->controls.rotate_left_pressed)
		g->player.dir = vectorf_rotate(g->player.dir, 2);
	else if (g->controls.rotate_right_pressed)
		g->player.dir = vectorf_rotate(g->player.dir, -2);
}

/* Collision is resolved using DDA which checks one grid in the direction of
 * movement of the player */
void	resolve_movement(t_game *g)
{
	const t_grid_coordsf	new_pos = move_player(g->player, &g->controls);
	const t_grid_coordsf	mdir = get_movement_dir(&g->controls, &g->player);

	if (g->controls.move_up_pressed)
		g->player.collision_point = check_wall_in_dir(&g->dp, g->player.pos,
				mdir, 1);
	else if (g->controls.move_down_pressed)
		g->player.collision_point = check_wall_in_dir(&g->dp, g->player.pos,
				mdir, 1);
	else if (g->controls.move_left_pressed)
		g->player.collision_point = check_wall_in_dir(&g->dp, g->player.pos,
				mdir, 1);
	else if (g->controls.move_right_pressed)
		g->player.collision_point = check_wall_in_dir(&g->dp, g->player.pos,
				mdir, 1);
	if (g->player.collision_point.x == -1 || !is_beyond(new_pos,
			g->player.collision_point, mdir))
		g->player.pos = new_pos;
}

bool	is_any_key_pressed(t_game *g)
{
	return (g->controls.rotate_right_pressed || g->controls.rotate_left_pressed
		|| g->controls.move_left_pressed || g->controls.move_right_pressed
		|| g->controls.move_down_pressed || g->controls.move_up_pressed);
}

void	update_game_state(t_game *g)
{
	g->player.collision_point = (t_grid_coordsf){.x = -1, .y = -1};
	if (is_any_key_pressed(g))
	{
		resolve_rotation(g);
		resolve_movement(g);
	}
}

void	render_graphics(t_game *g)
{
	t_grid_coordsf	ray;

	ray = check_wall_in_dir(&g->dp, g->player.pos, g->player.dir, 100);
	draw_grid(g);
	draw_square(&g->frame, grid_coordsf_to_pixel_point(g->player.pos), 25);
	draw_line(&g->frame, grid_coordsf_to_pixel_point(g->player.pos),
		grid_coordsf_to_pixel_point(ray));
	if (g->player.collision_point.x != -1)
	{
		draw_line(&g->frame, grid_coordsf_to_pixel_point(g->player.pos),
			grid_coordsf_to_pixel_point(g->player.collision_point));
		draw_hollow_square(&g->frame,
			grid_coordsf_to_pixel_point(g->player.collision_point), 25);
	}
	draw_hollow_square(&g->frame, grid_coordsf_to_pixel_point(ray), 25);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

/* Update and render loop for testing 2d plane */
int	testing_2d_plane_loop(t_game *g)
{
	update_game_state(g);
	render_graphics(g);
	return 0;
}

/* Allocates new image and initializes parameters of its struct */
int	init_image_data(void *mlx, t_img *img, int x, int y)
{
	img->dimensions = (t_vectori){.x = x * TILE_SIZE, .y = y * TILE_SIZE};
	img->img = mlx_new_image(mlx, img->dimensions.x, img->dimensions.y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	return 0;
}

int	init_mlx(t_game *g, int x, int y)
{
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, x * TILE_SIZE, y * TILE_SIZE, "Test");
	init_image_data(g->mlx, &g->frame, x, y);
	g->window_size = (t_pixel_point){.x = x * TILE_SIZE, .y = y * TILE_SIZE};
	g->player.pos = (t_vectorf){.x = 2.5, .y = 1.5};
	g->player.dir = (t_vectorf){.x = 1, .y = 0};
	g->player.dir = vectorf_rotate(g->player.dir, -225);
	g->map_size = (t_grid_coordsi){.x = 10, .y = 10}; // size of actual map
	return 0;
}

/* Draws a simple 2d plane for testing purposes
 * TODO: check for possible memory failures */
int	init_testing_2d_plane(void)
{
	static t_game	g;

	init_mlx(&g, 5, 5);
	mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);
	mlx_hook(g.win, 2, (1L << 0), handle_key_press, &g);
	mlx_hook(g.win, 3, (1L << 1), handle_key_release, &g);
	mlx_loop_hook(g.mlx, testing_2d_plane_loop, &g);
	mlx_loop(g.mlx);
	return 0;
}

int	main(void)
{
	return init_testing_2d_plane();
}
