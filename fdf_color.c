/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:43:27 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:34:09 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	split_color(int i, int j, char *map_split, t_map *map)
{
	char	**s_split_color;

	if (ft_strchr(map_split, ','))
	{
		s_split_color = ft_split(map_split, ',');
		if (!s_split_color)
			return (1);
		if (!is_altitude(s_split_color[0], j, map))
			return (1);
		map->altitude[i][j] = ft_atoi(s_split_color[0]);
		map->color[i][j] = ft_hexstr_to_int(s_split_color[1]);
		ft_free_all(s_split_color, NULL, NULL, 0);
	}
	else
	{
		if (!is_altitude(map_split, j, map))
			return (1);
		map->altitude[i][j] = ft_atoi(map_split);
		if (map->altitude[i][j])
			map->color[i][j] = 0x0000FF;
		else
			map->color[i][j] = 0xFFFFFF;
	}
	return (0);
}

int	is_altitude(char *altitude, int j, t_map *map)
{
	int	i;

	i = ft_strlen(altitude);
	if (j == map->width - 1 && altitude[i - 1] == '\n')
		i--;
	while (i > 0)
	{
		if (ft_isdigit(altitude[i - 1]) == 0 && altitude[0] != '-')
		{
			write(2, "Found wrong line length. Exiting.\n", 35);
			return (0);
		}
		i--;
	}
	return (1);
}

int	color_gradient(int line_color_start,
			int line_color_end, int nbr_pixel, int count)
{
	t_color	color_start;
	t_color	color_end;
	int		delta_r;
	int		delta_g;
	int		delta_b;

	color_start.r = ((line_color_start >> 16) & 0xFF);
	color_start.g = ((line_color_start >> 8) & 0xFF);
	color_start.b = ((line_color_start) & 0xFF);
	color_end.r = ((line_color_end >> 16) & 0xFF);
	color_end.g = ((line_color_end >> 8) & 0xFF);
	color_end.b = ((line_color_end) & 0xFF);
	delta_r = (color_end.r - color_start.r) / nbr_pixel;
	delta_g = (color_end.g - color_start.g) / nbr_pixel;
	delta_b = (color_end.b - color_start.b) / nbr_pixel;
	return (0 | ((color_start.r + (nbr_pixel - count) * delta_r) & 0xFF) << 16
		| ((color_start.g + (nbr_pixel - count) * delta_g) & 0xFF) << 8
		| ((color_start.b + (nbr_pixel - count) * delta_b) & 0xFF));
}
