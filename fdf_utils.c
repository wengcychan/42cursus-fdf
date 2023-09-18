/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:05:29 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:33:32 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_split(char **begin)
{
	int	count;

	count = 0;
	while (*begin)
	{
		count++;
		begin++;
	}
	return (count);
}

int	fill_altitude(t_map *map, char *s, char **map_split)
{
	int	j;

	j = 0;
	while (j < map->width)
	{
		if (split_color(map->height, j, map_split[j], map))
		{
			ft_free_all(map_split, s, NULL, 0);
			return (1);
		}
		j++;
	}
	ft_free_all(map_split, s, NULL, 0);
	map->height++;
	return (0);
}

int	find_n(char **begin)
{
	while (*begin)
	{
		if (*begin[0] == '\n')
			return (1);
		begin++;
	}
	return (0);
}

void	ft_free_pointer(int **pointer1, int **pointer2, int count)
{
	int	i;

	if (pointer1)
	{
		i = 0;
		while (i < count)
		{
			free(pointer1[i]);
			i++;
		}
		free(pointer1);
	}
	if (pointer2)
	{
		i = 0;
		while (i < count)
		{
			free(pointer2[i]);
			i++;
		}
		free(pointer2);
	}
}

void	ft_free_all(char **split, char *s, t_pos **coordinate, int count)
{
	int	i;

	if (split)
	{
		i = 0;
		while (i < count_split(split) + 1)
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
	if (s)
		free(s);
	if (coordinate)
	{
		i = 0;
		while (i < count)
		{
			free(coordinate[i]);
			i++;
		}
		free(coordinate);
	}
}
