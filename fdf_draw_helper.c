/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:05:29 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:36:01 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	malloc_coordinate(t_pos ***coordinate, t_map map)
{
	int	i;

	(*coordinate) = (t_pos **)malloc(map.height * sizeof(t_pos *));
	if (!(*coordinate))
		return (1);
	i = 0;
	while (i < map.height)
	{
		(*coordinate)[i] = (t_pos *)malloc(map.width * sizeof(t_pos));
		if (!(*coordinate)[i])
		{
			ft_free_all(NULL, NULL, (*coordinate), i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	set_origin(t_line *line, t_map map)
{
	int	landscape_width;
	int	landscape_height;
	int	landscape_width_offset;

	if (map.width < 100)
		line->scale = LINE_SCALE_SMALL_MAP;
	else
		line->scale = LINE_SCALE_LARGE_MAP;
	landscape_width = line->scale * map.projection_x * map.width
		+ line->scale * map.projection_x * map.height;
	landscape_width_offset = landscape_width / 2
		- line->scale * map.projection_x * map.height;
	line->origin_x = IMAGE_WIDTH / 2 - landscape_width_offset;
	landscape_height = line->scale * map.projection_y * map.height
		+ line->scale * map.projection_y * map.width;
	line->origin_y = (IMAGE_HEIGHT - landscape_height) / 2;
}

void	connect_row_point(t_line *line, t_pos **coordinate, t_map map,
		t_data *data)
{
	line->end_x = line->start_x + line->scale * map.projection_x;
	if (map.map_projection == 'o')
		line->end_y = line->start_y + line->scale * 0;
	else
		line->end_y = line->start_y + line->scale * map.projection_y;
	line->color_end = map.color[map.count_height][map.count_width];
	line->end_y_alt = line->end_y
		- map.altitude[map.count_height][map.count_width] * SCALE_Y;
	if (map.count_width < map.width)
	{
		coordinate[map.count_height][map.count_width].x = line->end_x;
		coordinate[map.count_height][map.count_width].y = line->end_y_alt;
		coordinate[map.count_height][map.count_width].color = line->color_end;
	}
	draw_line(data, *line);
	line->start_x = line->end_x;
	line->start_y = line->end_y;
	line->start_y_alt = line->end_y_alt;
	line->color_start = line->color_end;
}

void	draw_line(t_data *data, t_line line)
{
	t_delta	delta;
	t_pixel	pixel;
	int		nbr_pixel;
	int		count;

	delta.x = line.end_x - line.start_x;
	delta.y = line.end_y_alt - line.start_y_alt;
	nbr_pixel = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	count = nbr_pixel;
	delta.x /= nbr_pixel;
	delta.y /= nbr_pixel;
	pixel.x = line.start_x;
	pixel.y = line.start_y_alt;
	while (count)
	{
		pixel.color = color_gradient(line.color_start, line.color_end,
				nbr_pixel, count);
		my_mlx_pixel_put(data, pixel.x, pixel.y, pixel.color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		--count;
	}
}

void	print_instruction(void)
{
	ft_printf("\n------INSTRUCTION------\n\n");
	ft_printf("Move:\n W: Up\n A: Left\n S: Down\n D: Right\n\n");
	ft_printf("Rotate:\n X: Along x-axis\n Y: Along y-axis\n Z: Along z-axis\n\n");
	ft_printf("Zoom:\n Mouse scroll up: Zoom out\n Mouse scroll down: Zoom in\n\n");
	ft_printf("Close window:\n Esc\n\n");
}
