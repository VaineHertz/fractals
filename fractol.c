/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 10:01:14 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/12 17:15:32 by tpadilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			**get_palette(void)
{
	int		**palette;
	int		i;
	double	scale;
	int		base;

	scale = 255 / (MAX_ITER);
	i = -1;
	palette = (int**)malloc(sizeof(int*) * MAX_ITER);
	while (++i < MAX_ITER)
	{
		palette[i] = (int*)malloc(sizeof(int) * 3);
		palette[i][0] = 0 + (i * scale);
		palette[i][1] = 255 - (i * scale);
		palette[i][2] = 127;
	}
	return (palette);
}

void		useage_message(void)
{
	ft_putendl("\nusage: ./fractol fractal_number");
	ft_putendl("\nValid Fractal numbers:");
	ft_putendl("-----------------");
	ft_putendl("1: Mandelbrot Set\n2: Julia Set\n3: My Set\n");
	exit(0);
}

int			main(int argc, char **argv)
{
	t_fractol		*master;

	if (argc != 2)
	{
		useage_message();
		return (0);
	}
	master = init_master(argv[1]);
	iterate_windows_pixels(master);
	mlx_put_image_to_window(master->mlx_w->mlx, master->mlx_w->window,
			master->imge->image_p, 0, 0);
	mlx_key_hook(master->mlx_w->window, key_event, master);
	mlx_mouse_hook(master->mlx_w->window, mouse_event, master);
	mlx_hook(master->mlx_w->window, 6, 0, mouse_move, master);
	mlx_loop(master->mlx_w->mlx);
	return (0);
}
