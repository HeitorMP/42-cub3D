/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:31:08 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/27 09:49:22 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	find_zero(t_file *file, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y]) 
	{
		x = -1;
		while (map[y][++x]) 
		{
			if (map[y][x] == '0') 
			{
				file->x0 = x;
				file->y0 = y;
				break ;
			}
		}
		if (file->x0 != -1 && file->y0 != -1)
			return (0);
	}
	return (1);
}

static int	floodfill(char **array, int y, int x)
{
	if (y < 0 || x < 0 || !array[y] || (array[y] && array[y][x] == 32))
		return (1);
	else if (array[y][x] == '1')
		return (0);
	array[y][x] = '1';
	if (array [y + 1] && x > (int)(ft_strlen(array[y + 1]) - 1))
		return (1);
	if (y - 1 < 0 || (array [y - 1] && x > (int)(ft_strlen(array[y - 1]) - 1)))
		return (1);
	return (floodfill(array, y - 1, x)
		+ floodfill(array, y + 1, x)
		+ floodfill(array, y, x - 1)
		+ floodfill(array, y, x + 1));
}

int	checkmap(t_file *file, char **map)
{
	if (find_zero(file, map))
	{
		if (!floodfill(map, file->y, file->x))
			return (0);
	}
	while (!find_zero(file, map))
	{
		if (floodfill(map, file->y0, file->x0))
			return (1);
		file->x0 = -1;
		file->y0 = -1;
	}
	return (0);
}
