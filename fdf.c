/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:14:40 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:36:11 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc == 1 || argc > 2)
	{
		write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n", 46);
		return (1);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	vars.img.img = mlx_new_image(vars.mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
			&vars.img.bits_per_pixel, &vars.img.line_length,
			&vars.img.endian);
	if (fdf(&vars.img, argv, &vars.map, &vars.coordinate))
	{
		mlx_destroy_window(vars.mlx, vars.win);
		exit(0);
	}
	print_instruction();
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	register_event(&vars);
	ft_free_all(NULL, NULL, vars.coordinate, vars.map.height);
	ft_free_pointer(vars.map.altitude, vars.map.color, vars.map.height);
	return (0);
}

int	fdf(t_data *data, char **argv, t_map *map, t_pos ***coordinate)
{
	int	fd;

	map->map_projection = 'i';
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "No file ", 9);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		return (1);
	}
	if (read_map(fd, map))
		return (1);
	if (draw_wireframe(data, coordinate, *map))
		return (1);
	if (close(fd) == -1)
	{
		write(1, "close() error\n", 14);
		return (1);
	}
	return (0);
}

int	draw_wireframe(t_data *data, t_pos ***coordinate, t_map map)
{
	t_line	line;

	if (map.map_projection == 'o')
	{
		map.projection_x = cos(atan(0.5));
		map.projection_y = 0.5;
	}
	else
	{
		map.projection_x = cos(atan(0.5));
		map.projection_y = sin(atan(0.5));
	}
	set_origin(&line, map);
	if (malloc_coordinate(coordinate, map))
		return (1);
	map.count_height = 0;
	while (map.count_height < map.height)
	{
		draw_row(data, &line, *coordinate, map);
		map.count_height++;
	}
	return (0);
}

void	draw_row(t_data *data, t_line *line, t_pos **coordinate, t_map map)
{
	line->start_x = line->origin_x + map.count_height * (-line->scale
			* map.projection_x);
	line->start_y = line->origin_y + map.count_height * (line->scale
			* map.projection_y);
	map.count_width = 0;
	line->color_start = map.color[map.count_height][map.count_width];
	line->start_y_alt = line->start_y - map.altitude[map.count_height][0]
		* SCALE_Y;
	coordinate[map.count_height][map.count_width].x = line->start_x;
	coordinate[map.count_height][map.count_width].y = line->start_y_alt;
	coordinate[map.count_height][map.count_width].color = line->color_start;
	draw_column(line, coordinate, map, data);
	map.count_width++;
	while (map.count_width < map.width)
	{
		connect_row_point(line, coordinate, map, data);
		draw_column(line, coordinate, map, data);
		map.count_width++;
	}
}

void	draw_column(t_line *line, t_pos **coordinate, t_map map,
		t_data *data)
{
	if (map.count_height)
	{
		line->end_x = coordinate[map.count_height - 1][map.count_width].x;
		line->end_y_alt = coordinate[map.count_height - 1][map.count_width].y;
		line->color_end = coordinate[map.count_height
			- 1][map.count_width].color;
		draw_line(data, *line);
	}
}
