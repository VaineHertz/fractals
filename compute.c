/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 20:45:44 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/12 20:45:45 by tpadilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			escape_time(int px, int py, t_fractol *master)
{
	double	temp_x;
	double	x;
	double	y;
	double	xy0[2];
	int		i;

	xy0[0] = (px - WIN_WIDTH / 2) / (0.5 * ZOOM * WIN_WIDTH)
		+ master->mod->move_x / WIN_WIDTH;
	xy0[1] = (py - WIN_LENGTH / 2) / (0.5 * ZOOM * WIN_LENGTH)
		+ master->mod->move_y / WIN_LENGTH;
	x = master->option == 2 ? xy0[0] : 0.0;
	y = master->option == 2 ? xy0[1] : 0.0;
	xy0[0] = master->option == 2 ? master->mod->julia_x : xy0[0];
	xy0[1] = master->option == 2 ? master->mod->julia_y : xy0[1];
	i = 0;
	while (x * x + y * y < 2 * 2 && i < MAX_ITER - 1)
	{
		temp_x = x * x - y * y + xy0[0];
		y = 2 * x * y + xy0[1];
		x = temp_x;
		i++;
	}
	pixel_to_image(px, py, i, master);
}

double			radians(double number)
{
	return (number *= (3.14159265359 / 180));
}

void			tree_algorithm(double *xy1, double angle,
	int depth, t_fractol *master)
{
	double xy2[2];

	if (depth <= 0)
		return ;
	xy2[0] = xy1[0] + cos(radians(angle)) * depth * 3;
	xy2[1] = xy1[1] + sin(radians(angle)) * depth * 3;
	line(xy1, xy2, depth, master);
	tree_algorithm(xy2, angle - 10, depth - 1, master);
	tree_algorithm(xy2, angle + 10, depth - 1, master);
}

void			iterate_windows_pixels(t_fractol *master)
{
	int		x;
	int		y;
	double	xy[2];

	xy[0] = WIN_WIDTH / 2;
	xy[1] = WIN_LENGTH;
	x = 0;
	y = 0;
	if (master->option == 3)
		tree_algorithm(xy, -90, DEPTH, master);
	else if (master->option >= 1 && master->option <= 2)
	{
		while (y < WIN_LENGTH)
		{
			while (x < WIN_WIDTH)
			{
				escape_time(x, y, master);
				x++;
			}
			y++;
			x = 0;
		}
	}
	else
		useage_message();
}
