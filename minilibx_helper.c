/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:01:58 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:18:52 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < IMAGE_WIDTH && y < IMAGE_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	vars->keycode = keycode;
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2
		|| keycode == 6 || keycode == 16 || keycode == 7 || keycode == 31
		|| keycode == 34)
	{
		vars->tmp_img.img = mlx_new_image(vars->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
		vars->tmp_img.addr = mlx_get_data_addr(vars->tmp_img.img,
				&vars->tmp_img.bits_per_pixel, &vars->tmp_img.line_length,
				&vars->tmp_img.endian);
		if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
			translate(vars);
		else if (keycode == 16 || keycode == 7)
			rotate(vars);
		else if (keycode == 6)
			rotate_z(vars);
		else if (keycode == 31 || keycode == 34)
			change_projection(vars);
	}
	else if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	x = 0;
	y = 0;
	if (button == 4 || button == 5)
	{
		vars->tmp_img.img = mlx_new_image(vars->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
		vars->tmp_img.addr = mlx_get_data_addr(vars->tmp_img.img,
				&vars->tmp_img.bits_per_pixel, &vars->tmp_img.line_length,
				&vars->tmp_img.endian);
		if (button == 5)
		{
			vars->scale = ZOOM_OUT_SCALE;
			vars->current_scale *= ZOOM_OUT_SCALE;
		}
		else
		{
			vars->scale = ZOOM_IN_SCALE;
			vars->current_scale *= ZOOM_IN_SCALE;
		}
		zoom(vars);
	}
	return (0);
}

int	close_cross(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

void	register_event(t_vars *vars)
{
	vars->current_scale = 1;
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_mouse_hook(vars->win, mouse_hook, vars);
	mlx_hook(vars->win, 17, 0, close_cross, vars);
	mlx_loop(vars->mlx);
}
