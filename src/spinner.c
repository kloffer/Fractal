/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spinner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 15:44:01 by ikachko           #+#    #+#             */
/*   Updated: 2018/05/27 15:44:01 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_spinner(t_window *win)
{
	win->c_re = 1.5 * (win->x - WIN_WIDTH / 2) /
						(0.5 * win->zoom * WIN_WIDTH) + win->x1;
	win->c_im = 1.5 * (win->y - WIN_WIDTH / 2) /
						(0.5 * win->zoom * WIN_WIDTH) + win->y1;
	win->z_re = 0;
	win->z_im = 0;
	win->it = 0;
	while ((win->z_re * win->z_re + win->z_im * win->z_im) < 4
				&& win->it < win->it_max)
	{
		win->tmp = win->z_re;
		win->z_re = ((win->tmp * win->tmp) - (win->z_im * win->z_im))
																+ win->c_re;
		win->z_im = -2 * (win->tmp * win->z_im) + win->c_im;
		win->it++;
	}
	if (win->it == win->it_max)
		put_pxl_to_img(win, win->x, win->y, 0xFFFFFF);
	else
		put_pxl_to_img(win, win->x, win->y, win->color * win->it);
}

void	*spinner(void *win)
{
	t_window	*fract;
	double		tmp;

	fract = (t_window*)win;
	fract->x = 0;
	tmp = fract->y;
	while (fract->x < WIN_WIDTH)
	{
		fract->y = tmp;
		while (fract->y < fract->y_max)
		{
			calc_spinner(fract);
			fract->y++;
		}
		fract->x++;
	}
	return (win);
}

void	init_spinner(t_window *win)
{
	win->it_max = 200;
	win->zoom = 1;
	win->x1 = 0;
	win->y1 = 0;
	win->color = 513;
}

void	spinner_pthread(t_window *win)
{
	t_window	tab[10];
	pthread_t	t[10];
	int			i;

	i = 0;
	while (i < 10)
	{
		ft_memcpy((void*)&tab[i], (void*)win, sizeof(t_window));
		tab[i].y = 200 * i;
		tab[i].y_max = 200 * (i + 1);
		i++;
	}
	i = 0;
	while (++i <= 10)
		pthread_create(&t[i - 1], NULL, spinner, &tab[i - 1]);
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
