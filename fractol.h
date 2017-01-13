/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 09:42:26 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/12 16:42:57 by tpadilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# define WIN_WIDTH 500
# define WIN_LENGTH 500
# define MAX_ITER 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define DOWN_ARROW 125
# define UP_ARROW 126
# define ABS(a) ((a)<0?(-(a)):(a))
# define IMG_CHARP master->imge->image_char_p
# define ZOOM master->mod->zoom
# define PALETTE master->palette
# define PRTY master->color_party
# define DEPTH master->mod->depth

typedef struct	s_window_data
{
	void		*mlx;
	void		*window;
}				t_wdata;

typedef struct	s_mod_data
{
	double		move_x;
	double		move_y;
	double		mouse_x;
	double		mouse_y;
	double		julia_x;
	double		julia_y;
	double		zoom;
	int			depth;
	int			freeze;
	int			grow_tree;
}				t_mod;

typedef struct	s_image_data
{
	void		*image_p;
	char		*image_char_p;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_fractol_data
{
	t_wdata		*mlx_w;
	t_img		*imge;
	t_mod		*mod;
	int			color_party;
	int			option;
	int			**palette;
}				t_fractol;

t_wdata			*init_window(void);
t_img			*init_image(t_wdata *mlx_w);
void			reset_mod(t_fractol *master);
t_mod			*init_mod(void);
t_fractol		*init_master(char *str_option);
int				**get_palette(void);
void			useage_message(void);
int				main(int argc, char **argv);
int				key_event(int keycode, t_fractol *master);
int				mouse_event(int button, int x, int y, t_fractol *master);
int				mouse_move(int x, int y, t_fractol *master);
void			put_tree_to_image(int x, int y, int depth, t_fractol *master);
void			pixel_to_image(int px, int py, int iter, t_fractol *master);
void			line(double *pt1, double *pt2, int depth, t_fractol *master);
void			render_onevent(t_fractol *master);
void			iterate_windows_pixels(t_fractol *master);
void			tree_algorithm(double *xy1, double angle,
	int depth, t_fractol *master);
double			radians(double number);
void			escape_time(int px, int py, t_fractol *master);

#endif
