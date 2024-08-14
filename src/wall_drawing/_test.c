/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:04 by eandre            #+#    #+#             */
/*   Updated: 2024/08/14 21:24:26 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
# include <X11/XKBlib.h>
# include <X11/Xutil.h>

typedef struct s_win
{
	void	*mlx;
	void	*win;
	int		width;	
	int		height;	
}	t_win;
t_win	new_wind(int w, int h, char *str);


int	exit_hook_cross(t_win *win)
{
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	exit(0);
}

int	ft_event(int keysym, t_win *win)
{
	if (keysym == XK_Escape)
		exit_hook_cross(win);
	return (0);
}

//TODO
//line perpendicular to the vector of the player view
//



int	main()
{
	t_win	win;

	win = new_wind(500, 500, "pute");
	mlx_key_hook(win.win, ft_event, &win);
	mlx_hook(win.win, DestroyNotify, StructureNotifyMask,
		exit_hook_cross, &win);
	mlx_loop(win.mlx);
	mlx_destroy_window(win.mlx, win.win);
	free(win.mlx);
}


t_win	new_wind(int w, int h, char *str)
{
	void	*mlx;

	mlx = mlx_init();
	return ((t_win){mlx, mlx_new_window(mlx, w, h, str), w, h});
}