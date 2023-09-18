/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus_utils_rotate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:38:44 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:19:32 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_original_coordinate(t_pos ***coordinate,
								t_vars *vars)
{
	int	i;

	(*coordinate) = (t_pos **)malloc(vars->map.height * sizeof(t_pos *));
	if (!(*coordinate))
	{
		ft_free_pointer(vars->map.altitude, vars->map.color, vars->map.height);
		ft_free_all(NULL, NULL, vars->coordinate, vars->map.height);
		exit(0);
	}
	i = 0;
	while (i < vars->map.height)
	{
		(*coordinate)[i] = (t_pos *)malloc(vars->map.width * sizeof(t_pos));
		if ((*coordinate)[i] == NULL)
		{
			ft_free_pointer(vars->map.altitude,
				vars->map.color, vars->map.height);
			ft_free_all(NULL, NULL, (*coordinate), i);
			ft_free_all(NULL, NULL, vars->coordinate, vars->map.height);
			exit(0);
		}
		i++;
	}
	fill_original_coordinate(coordinate, vars);
}

void	fill_original_coordinate(t_pos ***original_coordinate,
									t_vars *vars)
{
	int	i;
	int	j;

	(*original_coordinate)[0][0].x = (vars->coordinate[0][0]).x;
	(*original_coordinate)[0][0].y = (vars->coordinate[0][0]).y;
	i = 0;
	while (i < vars->map.height)
	{
		j = 1;
		while (j < vars->map.width)
		{
			fill_row_coordinate(original_coordinate, vars, i, j);
			j++;
		}
		i++;
		fill_column_coordinate(original_coordinate, vars, i);
	}
}

void	fill_row_coordinate(t_pos ***original_coordinate,
							t_vars *vars, int i, int j)
{
	int	line_scale;

	if (vars->map.width < 100)
		line_scale = LINE_SCALE_SMALL_MAP;
	else
		line_scale = LINE_SCALE_LARGE_MAP;
	if (vars->map.map_projection == 'i')
	{
		(*original_coordinate)[i][j].x = (*original_coordinate)[i][j - 1].x
			+ line_scale * vars->current_scale * cos(atan(0.5));
		(*original_coordinate)[i][j].y = (*original_coordinate)[i][j - 1].y
			+ line_scale * vars->current_scale * sin(atan(0.5));
	}
	else
	{
		(*original_coordinate)[i][j].x = (*original_coordinate)[i][j - 1].x
			+ line_scale * vars->current_scale;
		(*original_coordinate)[i][j].y = (*original_coordinate)[i][j - 1].y;
	}
}

void	fill_column_coordinate(t_pos ***original_coordinate,
								t_vars *vars, int i)
{
	int	line_scale;

	if (vars->map.width < 100)
		line_scale = LINE_SCALE_SMALL_MAP;
	else
		line_scale = LINE_SCALE_LARGE_MAP;
	if (i < vars->map.height)
	{
		(*original_coordinate)[i][0].x = (*original_coordinate)[i - 1][0].x
			- line_scale * vars->current_scale * cos(atan(0.5));
		if (vars->map.map_projection == 'i')
			(*original_coordinate)[i][0].y = (*original_coordinate)[i - 1][0].y
				+ line_scale * vars->current_scale * sin(atan(0.5));
		else
			(*original_coordinate)[i][0].y = (*original_coordinate)[i - 1][0].y
				+ line_scale * vars->current_scale * 0.5;
	}
}

void	fill_rotate_coordinate(int i, int j, t_count count, t_vars *vars)
{
	vars->shifted.x = vars->original_coordinate[i][j].x
		- vars->original_coordinate[0][0].x;
	vars->shifted.y = vars->original_coordinate[i][j].y
		- vars->original_coordinate[0][0].y;
	if (vars->keycode == 16)
		(vars->coordinate)[i][j].x = vars->original_coordinate[0][0].x
			+ (vars->shifted.x * cos(ROTATE_ANGLE * (count.x + 1) * PI / 180)
				+ vars->map.altitude[i][j] * SCALE_Y * sin(ROTATE_ANGLE
					* (count.x + 1) * PI / 180));
	else
		(vars->coordinate)[i][j].y = vars->original_coordinate[0][0].y
			+ (vars->shifted.y * cos(ROTATE_ANGLE * (count.y + 1) * PI / 180)
				- vars->map.altitude[i][j] * SCALE_Y * 1.5 * sin(ROTATE_ANGLE
					* (count.y + 1) * PI / 180));
}
