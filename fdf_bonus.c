/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:40:16 by wchan             #+#    #+#             */
/*   Updated: 2023/09/20 15:26:01 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (vars->keycode == 0)
				vars->coordinate[i][j].x -= TRANSLATE_X;
			else if (vars->keycode == 2)
				vars->coordinate[i][j].x += TRANSLATE_X;
			else if (vars->keycode == 13)
				vars->coordinate[i][j].y -= TRANSLATE_Y;
			else
				vars->coordinate[i][j].y += TRANSLATE_Y;
			j++;
		}
		i++;
	}
	redraw(vars);
}

void	zoom(t_vars *vars)
{
	int		i;
	int		j;
	t_pos	midpoint;
	t_pos	shifted;

	midpoint = get_midpoint((vars->coordinate), vars->map);
	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			shifted.x = (vars->coordinate)[i][j].x - midpoint.x;
			shifted.y = (vars->coordinate)[i][j].y - midpoint.y;
			(vars->coordinate)[i][j].x = midpoint.x + (shifted.x * vars->scale);
			(vars->coordinate)[i][j].y = midpoint.y + (shifted.y * vars->scale);
			j++;
		}
		i++;
	}
	redraw(vars);
}

void	rotate(t_vars *vars)
{
	int				i;
	int				j;
	static t_count	count;

	set_original_coordinate(&(vars->original_coordinate),
		vars);
	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			fill_rotate_coordinate(i, j, count, vars);
			j++;
		}
		i++;
	}
	if (vars->keycode == 16)
		count.x++;
	else
		count.y++;
	redraw(vars);
	ft_free_all(NULL, NULL, vars->original_coordinate, vars->map.height);
}

void	rotate_z(t_vars *vars)
{
	int		i;
	int		j;
	t_pos	midpoint;
	t_pos	shifted;

	midpoint = get_midpoint((vars->coordinate), vars->map);
	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			shifted.x = (vars->coordinate)[i][j].x - midpoint.x;
			shifted.y = (vars->coordinate)[i][j].y - midpoint.y;
			(vars->coordinate)[i][j].x = midpoint.x + (shifted.x
					* cos(ROTATE_ANGLE * PI / 180)
					- shifted.y * sin(ROTATE_ANGLE * PI / 180));
			(vars->coordinate)[i][j].y = midpoint.y + (shifted.x
					* sin(ROTATE_ANGLE * PI / 180)
					+ shifted.y * cos(ROTATE_ANGLE * PI / 180));
			j++;
		}
		i++;
	}
	redraw(vars);
}

void	change_projection(t_vars *vars)
{
	ft_free_all(NULL, NULL, vars->coordinate, vars->map.height);
	if (vars->keycode == 34)
		vars->map.map_projection = 'i';
	else
		vars->map.map_projection = 'o';
	if (draw_wireframe(&vars->tmp_img, &vars->coordinate, vars->map))
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img = vars->tmp_img;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
