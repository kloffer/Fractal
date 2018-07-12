/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 12:32:14 by ikachko           #+#    #+#             */
/*   Updated: 2018/05/19 12:32:14 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800
# define WIN_NAME "FRACTOL"
# define CLICK_LEFT 1
# define CLICK_RIGHT 2
# define MOUSE_ZOOM_IN 5
# define MOUSE_ZOOM_OUT 4
# define ZOOM_IN 24
# define ZOOM_OUT 27
# define Z_UP 116
# define Z_DOWN 121
# define SPACE 32
# define UP 126
# define LEFT 123
# define DOWN 125
# define RIGHT 124
# define ESC 53
# define KEYPRESS	2
# define KEYPRESSMASK (1L<<0)
# define MIN(a,b) ((a < b) ? (a) : (b))
# define MAX(a,b) ((a > b) ? (a) : (b))

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*img_ptr;
	int			bpp;
	int			size_line;
	int			endian;
	int			color;
	int			fract;
	double		it;
	double		it_max;
	double		x;
	double		y;
	double		x1;
	double		y1;
	double		x2;
	double		y2;
	double		c_re;
	double		c_im;
	double		z_re;
	double		z_im;
	double		zoom;
	double		y_max;
	double		tmp;
}				t_window;

void			put_pxl_to_img(t_window *win, int x, int y, int color);
void			init_fractal(t_window *win);
int				key_handler(int key, void *param);
void			print_usage(void);
void			get_fractal(t_window *win, char *str);
int				mouse_move(int x, int y, t_window *win);
int				mouse_click(int key, int x, int y, t_window *win);

void			calc_mandelbrot(t_window *win);
void			*mandelbrot(void *win);
void			init_mandelbrot(t_window *win);
void			mandelbrot_pthread(t_window *win);

void			calc_julia(t_window *win);
void			*julia(void *win);
void			init_julia(t_window *win);
void			julia_pthread(t_window *win);

void			calc_burningship(t_window *win);
void			*burningship(void *win);
void			init_burningship(t_window *win);
void			burningship_pthread(t_window *win);

void			calc_spinner(t_window *win);
void			*spinner(void *win);
void			init_spinner(t_window *win);
void			spinner_pthread(t_window *win);

void			calc_bob(t_window *win);
void			*bob(void *win);
void			init_bob(t_window *win);
void			bob_pthread(t_window *win);

void			calc_kvitochka(t_window *win);
void			*kvitochka(void *win);
void			init_kvitochka(t_window *win);
void			kvitochka_pthread(t_window *win);
#endif
