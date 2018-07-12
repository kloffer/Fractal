/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 12:49:39 by ikachko           #+#    #+#             */
/*   Updated: 2018/05/20 17:23:20 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pxl_to_img(t_window *win, int x, int y, int color)
{
	if (win->x < WIN_WIDTH && win->y < WIN_WIDTH)
	{
		color = mlx_get_color_value(win->mlx_ptr, color);
		ft_memcpy(win->img + 4 * WIN_WIDTH * y + x * 4,
				&color, sizeof(int));
	}
}

void	string_keys(t_window *win)
{
	mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 10, 0xFFFFFF,
									"======= KEYS ======");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 50, 0xFFFFFF,
									"Move with arrows");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 70, 0xFFFFFF,
									"Zoom on mouse click, and mouse ball");
}

void	init_fractal(t_window *win)
{
	if (win->fract == 1)
		mandelbrot_pthread(win);
	if (win->fract == 2)
		julia_pthread(win);
	if (win->fract == 3)
		burningship_pthread(win);
	if (win->fract == 4)
		spinner_pthread(win);
	if (win->fract == 5)
		bob_pthread(win);
	if (win->fract == 6)
		kvitochka_pthread(win);
	string_keys(win);
}

void	print_usage(void)
{
	ft_putendl("Usage: ./fractol [fractol number]");
	ft_putendl("Fractals:");
	ft_putendl("1. Mandelbrot");
	ft_putendl("2. Julia");
	ft_putendl("3. Burningship");
	ft_putendl("4. Spinner");
	ft_putendl("5. Bob");
	ft_putendl("6. Kvitochka");
	exit(1);
}

int		main(int ac, char **av)
{
	t_window	*win;

	win = NULL;
	if (ac == 2)
	{
		win = (t_window*)ft_memalloc(sizeof(t_window));
		get_fractal(win, av[1]);
		win->mlx_ptr = mlx_init();
		win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_WIDTH,
											WIN_WIDTH, WIN_NAME);
		win->img_ptr = mlx_new_image(win->mlx_ptr, WIN_WIDTH, WIN_WIDTH);
		win->size_line = WIN_WIDTH;
		win->bpp = 32;
		win->endian = 0;
		win->img = mlx_get_data_addr(win->img_ptr, &win->bpp,
									&win->size_line, &win->endian);
		init_fractal(win);
		mlx_hook(win->win_ptr, KEYPRESS, KEYPRESSMASK, key_handler, win);
		mlx_mouse_hook(win->win_ptr, mouse_click, win);
		if (win->fract == 2)
			mlx_hook(win->win_ptr, 6, 0, mouse_move, win);
		mlx_loop(win->mlx_ptr);
	}
	else
		print_usage();
}
