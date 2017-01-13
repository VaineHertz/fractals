/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 20:39:18 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/12 20:39:19 by tpadilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void		reset_mod(t_fractol *master)
{
	master->mod->mouse_x = WIN_WIDTH / 2;
	master->mod->mouse_y = WIN_LENGTH / 2;
	master->mod->move_x = 0.0;
	master->mod->move_y = 0.0;
	ZOOM = 1;
}

t_mod		*init_mod(void)
{
	t_mod			*mod;

	mod = (t_mod*)malloc(sizeof(t_mod));
	mod->move_x = 0.0;
	mod->move_y = 0.0;
	mod->julia_x = -0.7;
	mod->julia_y = 0.27015;
	mod->zoom = 1;
	mod->freeze = -1;
	mod->grow_tree = -1;
	mod->depth = 2;
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
	PALETTE = get_palette();
	PRTY = -1;
	return (master);
}
