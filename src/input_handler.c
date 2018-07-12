/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 16:02:55 by ikachko           #+#    #+#             */
/*   Updated: 2018/05/27 16:02:55 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			mouse_move(int x, int y, t_window *win)
{
	win->c_im = 1.5 * (x - WIN_WIDTH / 2)
					/ (0.5 * win->zoom * WIN_WIDTH) + win->x1;
	win->c_re = (y - WIN_WIDTH / 2)
					/ (0.5 * win->zoom * WIN_WIDTH) + win->y1;
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	julia_pthread(win);
	return (1);
}

int			mouse_click(int key, int x, int y, t_window *win)
{
	if (key == CLICK_LEFT)
	{
		mlx_clear_window(win->mlx_ptr, win->win_ptr);
		win->x1 = 1.5 * (x - WIN_WIDTH / 2)
					/ (0.5 * win->zoom * WIN_WIDTH) + win->x1;
		win->y1 = (y - WIN_WIDTH / 2)
					/ (0.5 * win->zoom * WIN_WIDTH) + win->y1;
		win->zoom *= 1.1;
		init_fractal(win);
	}
	if (key == MOUSE_ZOOM_IN)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		win->zoom *= 1.1;
		init_fractal(win);
	}
	if (key == MOUSE_ZOOM_OUT)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		win->zoom /= 1.1;
		init_fractal(win);
	}
	return (1);
}

static void	move_fract(int key, t_window *win)
{
	if (key == UP)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		win->y1 -= 0.3 / win->zoom;
		init_fractal(win);
	}
	if (key == DOWN)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		win->y1 += 0.3 / win->zoom;
		init_fractal(win);
	}
	if (key == LEFT)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		win->x1 -= 0.3 / win->zoom;
		init_fractal(win);
	}
	if (key == RIGHT)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		win->x1 += 0.3 / win->zoom;
		init_fractal(win);
	}
}

int			key_handler(int key, void *param)
{
	t_window	*win;

	win = (t_window *)param;
	move_fract(key, win);
	if (key == ZOOM_IN)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		win->zoom *= 1.1;
		init_fractal(win);
	}
	if (key == ZOOM_OUT)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		win->zoom /= 1.1;
		init_fractal(win);
	}
	if (key == ESC)
	{
		mlx_clear_window((win)->mlx_ptr, (win)->win_ptr);
		free(win);
		system("leaks fractol");
		exit(0);
	}
	return (1);
}

void		get_fractal(t_window *win, char *str)
{
	int fract;

	fract = -1;
	if (str)
		fract = ft_atoi(str);
	if (fract > 0 && fract < 7)
	{
		win->fract = fract;
		if (fract == 1)
			init_mandelbrot(win);
		if (fract == 2)
			init_julia(win);
		if (fract == 3)
			init_burningship(win);
		if (fract == 4)
			init_spinner(win);
		if (fract == 5)
			init_bob(win);
		if (fract == 6)
			init_kvitochka(win);
	}
	else
		print_usage();
}
