/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:01:43 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:34:09 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define SCALE_Y 3
# define LINE_SCALE_SMALL_MAP 20
# define LINE_SCALE_LARGE_MAP 5
# define PI 3.141592654
# define START_X 500
# define START_Y 100
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define IMAGE_WIDTH 1920
# define IMAGE_HEIGHT 1080
# define TRANSLATE_X 20
# define TRANSLATE_Y 20
# define ZOOM_IN_SCALE 1.1
# define ZOOM_OUT_SCALE 0.9
# define ROTATE_ANGLE 20

# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdint.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_line
{
	int		start_x;
	int		start_y;
	int		start_y_alt;
	int		end_x;
	int		end_y;
	int		end_y_alt;
	int		color_start;
	int		color_end;
	int		origin_x;
	int		origin_y;
	int		scale;
}			t_line;

typedef struct s_pos
{
	double	x;
	double	y;
	int		color;
	int		count;
}			t_pos;

typedef struct s_map
{
	int		**altitude;
	int		**color;
	int		width;
	int		height;
	int		count_height;
	int		count_width;
	float	projection_x;
	float	projection_y;
	char	map_projection;
}			t_map;

typedef struct s_delta
{
	double	x;
	double	y;
}			t_delta;

typedef struct s_pixel
{
	double	x;
	double	y;
	int		color;
}			t_pixel;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}			t_color;

typedef struct s_count
{
	int		x;
	int		y;
}			t_count;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_data	tmp_img;
	t_pos	**coordinate;
	t_map	map;
	t_pos	**original_coordinate;
	t_pos	shifted;
	int		keycode;
	double	scale;
	double	current_scale;
}			t_vars;

int			fdf(t_data *data, char **argv, t_map *map,
				t_pos ***coordinate);
int			draw_wireframe(t_data *data, t_pos ***coordinate, t_map map);
void		draw_row(t_data *data, t_line *line, t_pos **coordinate,
				t_map map);
void		draw_column(t_line *line, t_pos **coordinate, t_map map,
				t_data *data);
int			read_map(int fd, t_map *map);
int			malloc_map_row(t_map *map, t_map map_tmp,
				char **map_split, char *s);
int			malloc_map_column(t_map *map, t_map map_tmp,
				char **map_split, char *s);
int			split_map(char ***map_split, t_map *map,
				t_map *map_tmp, char *s);
void		copy_altitude(t_map *map, t_map map_tmp);
int			fill_altitude(t_map *map, char *s, char **map_split);
int			set_altitude(t_map *map, char **s_split, char **map_split,
				int i);
int			malloc_coordinate(t_pos ***coordinate, t_map map);
void		set_origin(t_line *line, t_map map);
void		connect_row_point(t_line *line, t_pos **coordinate,
				t_map map, t_data *data);
void		draw_line(t_data *data, t_line line);
int			count_split(char **begin);
void		ft_free_pointer(int **pointer1, int **pointer2, int count);
void		ft_free_all(char **split, char *s, t_pos **coordinate, int count);
int			split_color(int i, int j, char *map_split, t_map *map);
int			is_altitude(char *altitude, int j, t_map *map);
int			color_gradient(int line_color_start, int line_color_end,
				int nbr_pixel, int count);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			key_hook(int keycode, t_vars *vars);
int			mouse_hook(int button, int x, int y, t_vars *vars);
int			close_cross(t_vars *vars);
void		register_event(t_vars *vars);
void		translate(t_vars *vars);
void		zoom(t_vars *vars);
void		rotate(t_vars *vars);
void		change_projection(t_vars *vars);
void		redraw(t_vars *vars);
void		redraw_row(t_pos **coordinate, t_data *data, t_map map);
void		redraw_column(t_pos **coordinate, t_data *data, t_map map);
int			ft_hexstr_to_int(char *hexstr);
int			ft_pow(int base, int pow);
t_pos		get_midpoint(t_pos **coordinate, t_map map);
void		print_instruction(void);
void		set_original_coordinate(t_pos ***coordinate,
				t_vars *vars);
void		fill_original_coordinate(t_pos ***original_oordinate,
				t_vars *vars);
void		fill_rotate_coordinate(int i, int j, t_count count,
				t_vars *vars);
void		fill_row_coordinate(t_pos ***original_coordinate,
				t_vars *vars, int i, int j);
void		fill_column_coordinate(t_pos ***original_coordinate,
				t_vars *vars, int i);
void		rotate_z(t_vars *vars);
int			find_n(char **begin);

#endif