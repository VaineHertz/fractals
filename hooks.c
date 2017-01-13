/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 20:45:47 by tpadilla          #+#    #+#             */
/*   Updated: 2017/01/12 20:45:49 by tpadilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			key_event(int keycode, t_fractol *master)
{
	if (keycode == 49)
		PRTY = -PRTY;
	else if (keycode == 3)
		master->mod->freeze = -master->mod->freeze;
	else if (keycode == 53)
		exit(0);
	else if (keycode == 15)
		reset_mod(master);
	else if (keycode == LEFT_ARROW)
		master->mod->move_x -= (0.1 * WIN_WIDTH) / ZOOM;
	else if (keycode == RIGHT_ARROW)
		master->mod->move_x += (0.1 * WIN_WIDTH) / ZOOM;
	else if (keycode == DOWN_ARROW)
	{
		DEPTH = DEPTH ? DEPTH - 1 : DEPTH;
		master->mod->move_y += (0.1 * WIN_LENGTH) / ZOOM;
	}
	else if (keycode == UP_ARROW)
	{
		DEPTH += 1;
		master->mod->move_y -= (0.1 * WIN_LENGTH) / ZOOM;
	}
	render_onevent(master);
	return (0);
}

int			mouse_event(int button, int x, int y, t_fractol *master)
{
	if (button == 4)
	{
		x -= WIN_WIDTH / 2;
		y -= WIN_LENGTH / 2;
		ZOOM *= 1.5;
		master->mod->move_x += x / ZOOM;
		master->mod->move_y += y / ZOOM;
	}
	else if (button == 5)
		ZOOM /= 1.5;
	if (master->option != 3)
		render_onevent(master);
	return (0);
}

int			mouse_move(int x, int y, t_fractol *master)
{
	if (master->mod->freeze == -1)
	{
		master->mod->julia_x = x * 4.0 / WIN_WIDTH - 2;
		master->mod->julia_y = y * 4.0 / WIN_LENGTH - 2;
	}
	if (master->option == 2)
		render_onevent(master);
	return (0);
}
