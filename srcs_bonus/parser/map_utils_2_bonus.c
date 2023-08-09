/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:40:58 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/23 16:40:58 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	error_edges(char *str)
{
	printf("%s", str);
	return (1);
}

/*Function to check the top edges of the player*/
static int	check_top_edges(t_file *file, char **map)
{
	int		y;
	int		x;

	x = file->x;
	y = file->y;
	if (y == 0 || x == 0 || x == (int)(ft_strlen(map[y]) - 1))
		return (error_edges("\033[0;34mError!\nPlayer on edges.\033[0m\n"));
	else if (y > 0 && x > (int)(ft_strlen(map[y - 1]) - 1))
		return (error_edges("\033[0;34mError!\nPlayer on edges.\033[0m\n"));
	else if (y > 0 && ft_isspace(map[y - 1][x]))
		return (error_edges("\033[0;34mError!\nPlayer on edges.\033[0m\n"));
	else if (y > 0 && x > 0 && ft_isspace(map[y][x - 1]))
		return (error_edges("\033[0;34mError!\nPlayer on edges.\033[0m\n"));
	else if (y > 0 && !map[y + 1])
		return (error_edges("\033[0;34mError!\nPlayer on edges.\033[0m\n"));
	else if (y > 0 && map[y +1] && x > (int)(ft_strlen(map[y + 1]) - 1))
		return (error_edges("\033[0;34mError!\nPlayer on edges.\033[0m\n"));
	return (0);
}

/*Function to check the bottom edges of the player*/
static int	check_bottom_edges(t_file *file, char **map)
{
	int		y;
	int		x;

	y = file->y;
	x = 0;
	while (map[y][x])
	{
		if (x >= file->x)
			return (0);
		x++;
	}
	printf("\033[0;34mError!\nCheck bottom of player edges.\033[0\n");
	return (1);
}

/*The original check_edges function can now be replaced with the following*/

int	check_edges(t_file *file, char **map)
{
	if (check_top_edges(file, map))
		return (1);
	if (check_bottom_edges(file, map))
		return (1);
	return (0);
}
