/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:31:08 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/26 13:06:02 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int find_zero(t_file *file, char **map)
{
	int y;
	int x;
	
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
				break;
			}
		}
	if (file->x0 != -1 && file->y0 != -1) // Sai do loop externo se a posição do jogador for encontrada
		return (0);
	}
	return (1);
}

/*int	checkmap(char **map, int x, int y)
{
	int	result;

	result = 0;
	if (map[y][x] == 'A' || map[y][x] == '1')
		return 1;
	if (map[y][x + 1] && !ft_isspace(map[y][x + 1]))
		return (1);
	if (map[y + 1] && ((int)ft_strlen(map[y + 1]) < x || !ft_isspace(map[y + 1][x])))
		return (1);
	if (x - 1 >= 0 && map[y][x - 1] && !ft_isspace(map[y][x - 1]))
		return (1);
	if (y - 1 >= 0 && ((int)ft_strlen(map[y - 1]) < x || !ft_isspace(map[y - 1][x])))
		return (1);
	map[y][x] = 'A';
	if (map[y][x + 1] && (map[y][x + 1] == '0' || map[y][x + 1] == 'D'))
		result += checkmap(map, x + 1, y);
	if (map[y + 1] && (int)ft_strlen(map[y + 1]) > x && (map[y + 1][x] == '0' \
		|| map[y + 1][x] == 'D'))
		result += checkmap(map, x, y + 1);
	if (y - 1 >= 0 && (int)ft_strlen(map[y - 1]) > x && (map[y - 1][x] == '0' \
		|| map[y - 1][x] == 'D'))
		result += checkmap(map, x, y - 1);
	if (x - 1 >= 0 && map[y][x - 1] && (map[y][x - 1] == '0' || \
		map[y][x - 1] == 'D'))
		result += checkmap(map, x - 1, y);
	return (result);
}*/

/*int	checkmap(char **map, int x, int y)
{
	int	result;

	result = 0;
	map[y][x] = 'A';
	if (map[y][x + 1] && map[y][x + 1] == ' ')
		return (1);
	if (map[y + 1] && ((int)ft_strlen(map[y + 1]) < x || map[y + 1][x] == ' '))
		return (1);
	if (x - 1 >= 0 && map[y][x - 1] && map[y][x - 1] == ' ')
		return (1);
	if (y - 1 >= 0 && ((int)ft_strlen(map[y - 1]) < x || map[y - 1][x] == ' '))
		return (1);
	if (map[y][x + 1] && (map[y][x + 1] == '0' || map[y][x + 1] == 'D'))
		result += checkmap(map, x + 1, y);
	if (map[y + 1] && (int)ft_strlen(map[y + 1]) > x && (map[y + 1][x] == '0' \
		|| map[y + 1][x] == 'D'))
		result += checkmap(map, x, y + 1);
	if (y - 1 >= 0 && (int)ft_strlen(map[y - 1]) > x && (map[y - 1][x] == '0' \
		|| map[y - 1][x] == 'D'))
		result += checkmap(map, x, y - 1);
	if (x - 1 >= 0 && map[y][x - 1] && (map[y][x - 1] == '0' || \
		map[y][x - 1] == 'D'))
		result += checkmap(map, x - 1, y);
	return (result);
}*/

/*int	checkmap(char **map, int x, int y)
{
	int	result;

	result = 0;
	map[y][x] = 'A';
	if (map[y][x] == 'A')
		return 1;
	if (map[y][x + 1] && map[y][x + 1] == ' ')
		return (1);
	if (map[y + 1] && (41 < x || map[y + 1][x] == ' '))
		return (1);
	if (x - 1 >= 0 && map[y][x - 1] && map[y][x - 1] == ' ')
		return (1);
	if (y - 1 >= 0 && (41 < x || map[y - 1][x] == ' '))
		return (1);
	if (y < 0 || y > mtr_len(map) || x < 0 || x > 41)
		return 1;
	if (map[y][x + 1] && (map[y][x + 1] == '0' || map[y][x + 1] == 'D'))
		result += checkmap(map, x + 1, y);
	if (map[y + 1] && 41 > x && (map[y + 1][x] == '0' \
		|| map[y + 1][x] == 'D'))
		result += checkmap(map, x, y + 1);
	if (y - 1 >= 0 && (int)ft_strlen(map[y - 1]) > x && (map[y - 1][x] == '0' \
		|| map[y - 1][x] == 'D'))
		result += checkmap(map, x, y - 1);
	if (x - 1 >= 0 && map[y][x - 1] && (map[y][x - 1] == '0' || \
		map[y][x - 1] == 'D'))
		result += checkmap(map, x - 1, y);
	return (result);
}*/

// int checkmap(char **map, int x, int y) 
// {
//     int result = 0;

// 	 if (map[y][x] == 'A' || map[y][x] == '1')
// 		return (1);
//     // Check if the current cell is outside the boundaries of the map or not a space (' ')
//     if (x < 0 || y < 0 || x > (int)(ft_strlen(map[y])) || !map[y])
//         return 1;
//     // Mark the current cell as visited (set it to 'A')
//     // if (map[y][x] == 'A' || map[y][x] == '1')
// 	// 	return (1);
// 	// map[y][x] = 'A';
//     // Check if the current cell is on the border and return 1 if it is
//     if (x == 0 || y == 0 || map[y][x + 1] == '\0' || map[y + 1] == NULL)
// 	{
//     	return (1);
// 	}
// 	map[y][x] = 'A';
//     // Recursively check adjacent cells in all four directions
//     result += checkmap(map, x + 1, y);
//     result += checkmap(map, x, y + 1);
//     result += checkmap(map, x - 1, y);
//     result += checkmap(map, x, y - 1);
//     return result;
// }


// static int	floodfill(char **array, int y, int x)
// {
	
// 	if (y < 0 || x < 0 || !array[y] || (array[y] && !array[y][x]))
// 		return (1);
// 	else if (array[y][x] == '1')
// 		return (0);
// 	array[y][x] = '1';
// 	if (array [y + 1] && x > (int)(ft_strlen(array[y + 1]) - 1))
// 		return 1;
// 	if (y - 1 < 0 || (array [y - 1] && x > (int)(ft_strlen(array[y - 1]) - 1)))
// 		return 1;
// 	return (floodfill(array, y - 1, x)
// 		+ floodfill(array, y + 1, x)
// 		+ floodfill(array, y, x - 1)
// 		+ floodfill(array, y, x + 1));
// }

static int	floodfill(char **array, int y, int x)
{
	
	if (y < 0 || x < 0 || !array[y] || (array[y] && ft_isspace(array[y][x])))
		return (1);
	else if (array[y][x] == '1')
		return (0);
	array[y][x] = '1';
	if (array [y + 1] && x > (int)(ft_strlen(array[y + 1]) - 1))
		return 1;
	if (y - 1 < 0 || (array [y - 1] && x > (int)(ft_strlen(array[y - 1]) - 1)))
		return 1;
	return (floodfill(array, y - 1, x)
		+ floodfill(array, y + 1, x)
		+ floodfill(array, y, x - 1)
		+ floodfill(array, y, x + 1));
}

int checkmap(t_file *file, char **map)
{
	int result;
	// int zero;

	result = 0;
	// zero = 0;
	find_zero(file, map);
	result = floodfill(map, file->y0, file->x0);
	while (!find_zero(file, map))
	{
		if (floodfill(map, file->y0, file->x0))
			return (1);
		file->x0 = -1;
		file->y0 = -1;
	}
	// printf("%d", result);
	return (result);
}