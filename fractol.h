/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 09:42:26 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/11 19:45:49 by tpadilla         ###   ########.fr       */
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

typedef struct	s_window_data
{
	void		*mlx;
	void		*window;
}				t_wdata;

typedef struct	s_mod_data
{
	double		move_x;
	double		move_y;
	double		zoom;
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
	int			**pallete;
}				t_fractol;

#endif
