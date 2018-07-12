/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 15:47:08 by ikachko           #+#    #+#             */
/*   Updated: 2018/05/27 15:47:09 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_julia(t_window *win)
{
	win->z_re = 1.5 * (win->x - WIN_WIDTH / 2)
				/ (0.5 * win->zoom * WIN_WIDTH) + win->x1;
	win->z_im = 1.5 * (win->y - WIN_WIDTH / 2)
				/ (0.5 * win->zoom * WIN_WIDTH) + win->y1;
	win->it = 0;
	while ((win->z_re * win->z_re + win->z_im * win->z_im) < 4
											&& win->it < win->it_max)
	{
		win->tmp = win->z_re;
		win->z_re = win->z_re * win->z_re - win->z_im * win->z_im + win->c_re;
		win->z_im = 2 * win->z_im * win->tmp + win->c_im;
		win->it++;
	}
	if (win->it == win->it_max)
		put_pxl_to_img(win, win->x, win->y, 0xFFFFFF);
	else
		put_pxl_to_img(win, win->x, win->y, win->color * win->it);
}

void	*julia(void *win)
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
			calc_julia(fract);
			fract->y++;
		}
		fract->x++;
	}
	return (win);
}

void	init_julia(t_window *win)
{
	win->it_max = 100;
	win->zoom = 1;
	win->x1 = 0;
	win->y1 = 0;
	win->color = 10666;
	win->c_re = -0.8;
	win->c_im = 0.156;
}

void	julia_pthread(t_window *win)
{
	t_window	tab[20];
	pthread_t	t[20];
	int			i;

	i = 0;
	while (i < 20)
	{
		ft_memcpy((void*)&tab[i], (void*)win, sizeof(t_window));
		tab[i].y = 100 * i;
		tab[i].y_max = 100 * (i + 1);
		i++;
	}
	i = 0;
	while (++i <= 20)
		pthread_create(&t[i - 1], NULL, julia, &tab[i - 1]);
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
