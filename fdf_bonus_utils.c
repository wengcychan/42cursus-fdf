/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:40:16 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 17:34:00 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	redraw(t_vars *vars)
{
	redraw_row(vars->coordinate, &vars->tmp_img, vars->map);
	redraw_column(vars->coordinate, &vars->tmp_img, vars->map);
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img = vars->tmp_img;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	redraw_row(t_pos **coordinate, t_data *data, t_map map)
{
	t_line	line;
	int		i;
	int		j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width - 1)
		{
			line.start_x = coordinate[i][j].x;
			line.start_y_alt = coordinate[i][j].y;
			line.color_start = coordinate[i][j].color;
			line.end_x = coordinate[i][j + 1].x;
			line.end_y_alt = coordinate[i][j + 1].y;
			line.color_end = coordinate[i][j + 1].color;
			draw_line(data, line);
			j++;
		}
		i++;
	}
}

void	redraw_column(t_pos **coordinate, t_data *data, t_map map)
{
	t_line	line;
	int		i;
	int		j;

	i = 0;
	while (i < map.height - 1)
	{
		j = 0;
		while (j < map.width)
		{
			line.start_x = coordinate[i][j].x;
			line.start_y_alt = coordinate[i][j].y;
			line.color_start = coordinate[i][j].color;
			line.end_x = coordinate[i + 1][j].x;
			line.end_y_alt = coordinate[i + 1][j].y;
			line.color_end = coordinate[i + 1][j].color;
			draw_line(data, line);
			j++;
		}
		i++;
	}
}

t_pos	get_midpoint(t_pos **coordinate, t_map map)
{
	t_pos	midpoint;

	midpoint.x = (coordinate[0][map.width - 1].x + coordinate[map.height
			- 1][0].x) / 2;
	midpoint.y = (coordinate[0][0].y + coordinate[map.height - 1][map.width
			- 1].y) / 2;
	return (midpoint);
}
