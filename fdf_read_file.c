/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:31:44 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:31:58 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_map(int fd, t_map *map)
{
	char	*s;
	t_map	map_tmp;
	char	**map_split;

	map->height = 0;
	s = "1";
	map_tmp.altitude = NULL;
	map_tmp.color = NULL;
	while (s)
	{
		s = get_next_line(fd);
		if (s)
		{
			if (split_map(&map_split, map, &map_tmp, s))
				return (1);
			if (malloc_map_row(map, map_tmp, map_split, s))
				return (1);
			if (malloc_map_column(map, map_tmp, map_split, s))
				return (1);
			copy_altitude(map, map_tmp);
			if (fill_altitude(map, s, map_split))
				return (1);
		}
	}
	return (0);
}

int	split_map(char ***map_split, t_map *map, t_map *map_tmp, char *s)
{
	*map_split = ft_split(s, ' ');
	if (!(*map_split))
	{
		free(s);
		if (map->height)
			ft_free_pointer(map->altitude, map->color, map->height);
		return (1);
	}
	if (!map->height)
		map->width = count_split(*map_split) - find_n(*map_split);
	else if (count_split(*map_split) - find_n(*map_split) != map->width)
	{
		ft_free_all(*map_split, s, NULL, 0);
		ft_free_pointer(map->altitude, map->color, map->height);
		write(2, "Found wrong line length. Exiting.\n", 35);
		return (1);
	}
	if (map->height)
	{
		map_tmp->altitude = map->altitude;
		map_tmp->color = map->color;
	}
	return (0);
}

int	malloc_map_row(t_map *map, t_map map_tmp, char	**map_split, char *s)
{
	map->altitude = (int **)malloc(sizeof(int *) * (map->height + 1));
	if (!map->altitude)
	{
		ft_free_all(map_split, s, NULL, 0);
		ft_free_pointer(map_tmp.altitude, map_tmp.color, map->height);
		return (1);
	}
	map->color = (int **)malloc(sizeof(int *) * (map->height + 1));
	if (!map->color)
	{
		ft_free_all(map_split, s, NULL, 0);
		ft_free_pointer(map->altitude, NULL, 0);
		ft_free_pointer(map_tmp.altitude, map_tmp.color, map->height);
		return (1);
	}
	return (0);
}

int	malloc_map_column(t_map *map, t_map map_tmp, char **map_split, char *s)
{
	int	i;

	i = 0;
	while (i < map->height + 1)
	{
		map->altitude[i] = (int *)malloc(sizeof(int) * map->width);
		if (!map->altitude[i])
		{
			ft_free_all(map_split, s, NULL, 0);
			ft_free_pointer(map->altitude, map->color, i);
			ft_free_pointer(map_tmp.altitude, map_tmp.color, map->height);
			return (1);
		}
		map->color[i] = (int *)malloc(sizeof(int) * map->width);
		if (!map->color[i])
		{
			ft_free_all(map_split, s, NULL, 0);
			ft_free_pointer(map->altitude, map->color, i + 1);
			ft_free_pointer(map_tmp.altitude, map_tmp.color, map->height);
			return (1);
		}
		i++;
	}
	return (0);
}

void	copy_altitude(t_map *map, t_map map_tmp)
{
	int	i;
	int	j;

	if (map->height)
	{
		i = 0;
		while (i < map->height)
		{
			j = 0;
			while (j < map->width)
			{
				map->altitude[i][j] = map_tmp.altitude[i][j];
				map->color[i][j] = map_tmp.color[i][j];
				j++;
			}
			i++;
		}
		ft_free_pointer(map_tmp.altitude, map_tmp.color, map->height);
	}
}
