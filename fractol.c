/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 10:01:14 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/11 16:23:28 by tpadilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			**get_pallete(void)
{
	int		**pallete;
	int		i;
	double	scale;
	int		base;

	scale = 255 / (MAX_ITER / 2);
	i = -1;
	pallete = (int**)malloc(sizeof(int*) * MAX_ITER);
	while (++i < MAX_ITER)
	{
		pallete[i] = (int*)malloc(sizeof(int) * 3);
		pallete[i][0] = 0 + (i * scale);
		pallete[i][1] = 255 - (i * scale);
		pallete[i][2] = 127;
	}
	i = -1;
	return (pallete);
}

void		pixel_to_image(int px, int py, int iter, t_fractol *master)
{
	int	i;

	i = ((4 * px) + (py * master->imge->size_line));
	master->imge->image_char_p[i] = master->pallete[iter][2];
	master->imge->image_char_p[i + 1] = master->pallete[iter][1];
	master->imge->image_char_p[i + 2] = master->pallete[iter][0];
}

t_wdata		*init_window(void)
{
	t_wdata			*mlx_w;

	mlx_w = (t_wdata*)malloc(sizeof(t_wdata));
	mlx_w->mlx = mlx_init();
	mlx_w->window = mlx_new_window(mlx_w->mlx,
			WIN_WIDTH, WIN_LENGTH, "Fractol");
	return (mlx_w);
}

t_img		*init_image(t_wdata *mlx_w)
{
	t_img			*imge;

	imge = (t_img*)malloc(sizeof(t_img));
	imge->image_p = mlx_new_image(mlx_w->mlx, WIN_WIDTH, WIN_LENGTH);
	imge->image_char_p = mlx_get_data_addr(imge->image_p,
			&imge->bpp, &imge->size_line, &imge->endian);
	return (imge);
}

t_fractol	*init_master(void)
{
	t_fractol		*master;

	master = (t_fractol*)malloc(sizeof(t_fractol));
	master->mlx_w = init_window();
	master->imge = init_image(master->mlx_w);
	master->pallete = get_pallete();
	return (master);
}

void		escape_time(int px, int py, t_fractol *master)
{
	double	temp_x;
	double	x;
	double	y;
	double	x0;
	double	y0;
	int		i;

	x = 0.0;
	y = 0.0;
	x0 = 1.5 * (px - WIN_WIDTH / 2) / (0.5 * WIN_WIDTH) + (-(0.5));
	y0 = (py - WIN_LENGTH / 2) / (0.5 * WIN_LENGTH) + 0;
	i = 0;
	while (x * x + y * y < 2 * 2 && i < MAX_ITER - 1)
	{
		temp_x = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = temp_x;
		i++;
	}
	pixel_to_image(px, py, i, master);
}

void		mandelbrot(t_fractol *master)
{
	int x;
	int y;

	x = 0;
	y = 0;
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
	ft_putendl("happy face :)");
}

void		fractol_manager(t_fractol *master, char *str_option)
{
	int				option;

	option = ft_atoi(str_option);
	if (option == 1)
		mandelbrot(master);
	else if (option == 2)
//		julia(master);
		;
	else if (option == 3)
//		my_set(master);
		;
}

/*int			key_event(int keycode, t_fractol *master)
{
	ft_putnbr(keycode);
	ft_putendl("<- keycode");
	return (0);
}*/

int			main(int argc, char **argv)
{
	t_fractol		*master;

	if (argc != 2)
	{
		ft_putendl("\nusage: ./fractol fractal_number\n\nValid Fractal numbers:");
		ft_putendl("-----------------");
		ft_putendl("1: Mandelbrot Set\n2: Julia Set\n3: My Set\n");
		return (0);
	}
	master = init_master();
	fractol_manager(master, argv[1]);
	mlx_put_image_to_window(master->mlx_w->mlx, master->mlx_w->window,
			master->imge->image_p, 0, 0);
//	mlx_key_hook(master->mlx_w->mlx, key_event, master);
	mlx_loop(master->mlx_w->mlx);
	return (0);
}
