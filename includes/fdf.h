/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:42:25 by ikachko           #+#    #+#             */
/*   Updated: 2018/04/23 13:42:25 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# define WIN_WIDTH 2048
# define WIN_HEIGHT 1024
# define WIN_NAME "FDF"
# define A 0
# define S 1
# define D 2
# define F 3
# define Q 12
# define W 13
# define E 14
# define R 15
# define P 35
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
# define MATRIX(window, j, i) window->win_matrix.matrix[j][i]
# define MATR_SIZE(window) window->win_matrix.matrix_size
# define M_P(win) win->mlx_ptr
# define W_P(win) win->win_ptr
# define KEYPRESS	2
# define KEYPRESSMASK (1L<<0)

typedef struct					s_vector3
{
	int							x;
	int							y;
	int							z;
	int							color;
}								t_vect3;

typedef struct					s_vector2
{
	int							x;
	int							y;
	int							color;

}								t_vect2;

typedef	struct					s_map_size
{
	int							width;
	int							height;
}								t_map_size;

typedef struct					s_r_xyz
{
	double						rx;
	double						ry;
	double						rz;
}								t_r_xyz;

typedef struct					s_matrix
{
	t_vect3						**matrix;
	t_map_size					matrix_size;
	t_r_xyz						r_xyz;
}								t_matrix;

typedef struct					s_window
{
	void						*mlx_ptr;
	void						*win_ptr;
	t_map_size					win_size;
	t_matrix					win_matrix;
}								t_window;

int								valid_color(char *line);
void							color_grad(t_window *win);
void							clear_str2(char ***str);
void							clear_matrix(t_window *win);
int								file_open(char *filename);
char							**ft_read_matrix(char *filename);
t_matrix						get_matrix(char **map);
t_map_size						get_map_size(char **map);
int								ft_validator(char **matrix);
void							ft_error(char *error_str);
int								count_numbers(char *line);
void							print_line_matrix(t_window *win);
void							line_draw(t_vect2 start, t_vect2 end,
										t_window *win);
t_vect2							get_win_deltas(t_window *win);
t_vect3							ft_new_vector3(int y, int x, int z, int color);
t_vect2							ft_new_vector2(int y, int x, int color);
t_r_xyz							ft_new_angles(int rx, int ry, int rz);
void							move_x(t_window *win, int coeff);
void							move_y(t_window *win, int coeff);
void							move_z(t_window *win, double coeff);
void							rotate_x(t_window *win, double coeff);
void							rotate_y(t_window *win, double coeff);
void							rotate_z(t_window *win, double coeff);
void							vector_sum(t_window *win, int coeff);
void							vector_x_move(t_window *win, int coeff);
void							vector_y_move(t_window *win, int coeff);
void							vector_z_move(t_window *win, int coeff);
void							vector_xyz_move(t_window *win, int dx,
															int dy, int dz);
void							move_r_xyz(t_window *win, double coeff);
void							move_r_x(t_window *win, double coeff);
void							move_r_y(t_window *win, double coeff);
void							move_r_z(t_window *win, double coeff);
int								min(int a, int b);
int								max(int a, int b);
int								sign(int x);
t_vect2							*ft_new_vect2(int y, int x, int color);
t_vect3							*ft_new_vect3(int y, int x, int z, int color);
int								key_handler(int key, void *param);
t_vect2							get_center(t_map_size map_size);
t_vect3							get_coord_center(t_window *win);
t_window						*init_window(void);
void							correct_size(t_window *win);
t_vect2							xyz_xy(t_vect3 old_vector, t_r_xyz xyz,
														t_window *win);
void							stretch_z(t_window *win, double coeff);
void							vector_prod(t_window *win, double coeff);
#endif
