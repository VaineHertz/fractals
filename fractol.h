/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 09:42:26 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/11 16:21:36 by tpadilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# define WIN_WIDTH 1500
# define WIN_LENGTH 1000
# define MAX_ITER 256
# define X master->cds->x
# define Y master->cds->y

typedef struct	s_window_data
{
	void		*mlx;
	void		*window;
}				t_wdata;

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
	int			**pallete;
}				t_fractol;

#endif
