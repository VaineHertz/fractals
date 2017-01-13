/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 20:45:52 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/12 20:45:54 by tpadilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		put_tree_to_image(int x, int y, int depth, t_fractol *master)
{
	int i;

	i = ((4 * x) + (y * master->imge->size_line));
	if (x < WIN_WIDTH && x > 0 && y < WIN_LENGTH && y > 0)
	{
		if (depth > DEPTH / 2)
		{
			IMG_CHARP[i] = 18;
			IMG_CHARP[i + 1] = 72;
			IMG_CHARP[i + 2] = 122;
		}
		else
		{
			IMG_CHARP[i] = 19;
			IMG_CHARP[i + 1] = 142;
			IMG_CHARP[i + 2] = 0;
		}
	}
}

void		pixel_to_image(int px, int py, int iter, t_fractol *master)
{
	int	i;

	i = ((4 * px) + (py * master->imge->size_line));
	IMG_CHARP[i] = PRTY == 1 ?
		PALETTE[iter][2] * ZOOM : PALETTE[iter][2];
	IMG_CHARP[i + 1] = PRTY == 1 ?
		PALETTE[iter][1] * ZOOM : PALETTE[iter][1];
	IMG_CHARP[i + 2] = PRTY == 1 ?
		PALETTE[iter][0] + ZOOM : PALETTE[iter][0];
}

void		line(double *pt1, double *pt2, int depth, t_fractol *master)
{
	int			*xyz_diff;
	int			length;
	int			max;
	double		xy[2];

	xyz_diff = (int*)malloc(sizeof(int) * 2);
	xy[0] = 100000 * pt1[0];
	xy[1] = 100000 * pt1[1];
	xyz_diff[0] = pt1[0] - pt2[0];
	xyz_diff[1] = pt1[1] - pt2[1];
	if (ABS(xyz_diff[0]) > ABS(xyz_diff[1]) ||
			ABS(xyz_diff[0]) == ABS(xyz_diff[1]))
		length = ABS(xyz_diff[0]);
	else if (ABS(xyz_diff[0]) < ABS(xyz_diff[1]))
		length = ABS(xyz_diff[1]);
	max = length + 1;
	while (--max)
	{
		xy[0] -= (xyz_diff[0] * 100000) / length;
		xy[1] -= (xyz_diff[1] * 100000) / length;
		put_tree_to_image((xy[0] / 100000), (xy[1] / 100000), depth, master);
	}
}

void		render_onevent(t_fractol *master)
{
	master->imge->image_p = mlx_new_image(master->mlx_w->mlx,
		WIN_WIDTH, WIN_LENGTH);
	IMG_CHARP = mlx_get_data_addr(master->imge->image_p,
		&master->imge->bpp, &master->imge->size_line,
		&master->imge->endian);
	iterate_windows_pixels(master);
	mlx_put_image_to_window(master->mlx_w->mlx, master->mlx_w->window,
		master->imge->image_p, 0, 0);
}
