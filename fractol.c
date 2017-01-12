/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 10:01:14 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/11 19:57:10 by tpadilla         ###   ########.fr       */
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
	master->imge->image_char_p[i] = master->color_party == 1 ? master->pallete[iter][2] * master->mod->zoom : master->pallete[iter][2];
	master->imge->image_char_p[i + 1] = master->color_party == 1 ? master->pallete[iter][1] * master->mod->zoom : master->pallete[iter][1];
	master->imge->image_char_p[i + 2] = master->color_party == 1 ? master->pallete[iter][0] + master->mod->zoom : master->pallete[iter][0];
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

t_mod		*init_mod(void)
{
	t_mod			*mod;

	mod = (t_mod*)malloc(sizeof(t_mod));
	mod->move_x = (-0.5);
	mod->move_y = 0.0;
	mod->zoom = 1;
	return (mod);
}

t_fractol	*init_master(char *str_option)
{
	t_fractol		*master;

	master = (t_fractol*)malloc(sizeof(t_fractol));
	master->option = ft_atoi(str_option);
	master->mlx_w = init_window();
	master->imge = init_image(master->mlx_w);
	master->mod = init_mod();
	master->pallete = get_pallete();
	master->color_party = -1;
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
	x0 = 1.5 * (px - WIN_WIDTH / 2) / (0.5 * master->mod->zoom * WIN_WIDTH) + master->mod->move_x;
	y0 = (py - WIN_LENGTH / 2) / (0.5 * master->mod->zoom * WIN_LENGTH) + master->mod->move_y;
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
}

void		fractol_manager(t_fractol *master)
{
	if (master->option == 1)
		mandelbrot(master);
	else if (master->option == 2)
//		julia(master);
		;
	else if (master->option == 3)
//		my_set(master);
		;
	else
	{
		ft_putendl("\nusage: ./fractol fractal_number\n\nValid Fractal numbers:");
		ft_putendl("-----------------");
		ft_putendl("1: Mandelbrot Set\n2: Julia Set\n3: My Set\n");
		exit(0);
	}	
}

int			key_event(int keycode, t_fractol *master)
{
	if (keycode == 49)
	{
		master->color_party = -master->color_party;
		ft_putnbr(master->color_party);
	}
	else if (keycode == LEFT_ARROW)
		master->mod->move_x += 0.1 / master->mod->zoom;
	else if (keycode == RIGHT_ARROW)
		master->mod->move_x -= 0.1 / master->mod->zoom;
	else if (keycode == DOWN_ARROW)
		master->mod->move_y -= 0.1 / master->mod->zoom;
	else if (keycode == UP_ARROW)
		master->mod->move_y += 0.1 / master->mod->zoom;
	master->imge->image_p = mlx_new_image(master->mlx_w->mlx,
			WIN_WIDTH, WIN_LENGTH);
	master->imge->image_char_p = mlx_get_data_addr(master->imge->image_p,
			&master->imge->bpp, &master->imge->size_line,
			&master->imge->endian);
	fractol_manager(master);
	mlx_put_image_to_window(master->mlx_w->mlx, master->mlx_w->window,
			master->imge->image_p, 0, 0);
	return (0);
}

int			mouse_event(int button, int x, int y, t_fractol *master)
{	
	if (button == 4)
		master->mod->zoom *= 1.5;
	else if (button == 5)
		master->mod->zoom /= 1.5;
	master->imge->image_p = mlx_new_image(master->mlx_w->mlx,
			WIN_WIDTH, WIN_LENGTH);
	master->imge->image_char_p = mlx_get_data_addr(master->imge->image_p,
			&master->imge->bpp, &master->imge->size_line,
			&master->imge->endian);
	fractol_manager(master);
	mlx_put_image_to_window(master->mlx_w->mlx, master->mlx_w->window,
			master->imge->image_p, 0, 0);
	return (0);
}

int			mouse_move(int x, int y, t_fractol *master)
{
	return (0);
}

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
	master = init_master(argv[1]);
	fractol_manager(master);
	mlx_put_image_to_window(master->mlx_w->mlx, master->mlx_w->window,
			master->imge->image_p, 0, 0);
	mlx_key_hook(master->mlx_w->window, key_event, master);
	mlx_mouse_hook(master->mlx_w->window, mouse_event, master);
	mlx_hook(master->mlx_w->window, 6, 0, mouse_move, master);
	mlx_loop(master->mlx_w->mlx);
	return (0);
}
