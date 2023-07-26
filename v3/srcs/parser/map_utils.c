/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:40:58 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/26 22:19:24 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_trim_end(const char *str)
{
	char		*result;
	const char	*end;
	const char	*start;
	size_t		size;
	size_t		i;

	if (!str)
		return (NULL);
	if (*str == '\0')
	{
		result = malloc(1);
		if (result)
			result[0] = '\0';
		return (result);
	}
	start = str;
	end = str;
	while (*end)
		end++;
	end--;
	while (end >= str && ft_isspace(*end))
		end--;
	size = end - start + 1;
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = str[i];
		i++;
	}
	result[size] = '\0';
	return (result);
}

static int	check_edges(t_file *file, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y] && y <= file->y) 
	{
		x = 0;
		while (map[y][x]) 
		{
			if (y == file->y && y > 0 && file->x > (int)(ft_strlen(map[y - 1]) - 1)) 
			{
				printf("\033[0;34mError!\nCheck top of player edges.\033[0\n");
				return (1);
			}
			else if (y == file->y && y > 0 && (ft_isspace(map[file->y - 1][file->x])))
			{
				printf("\033[0;34mError!\nCheck top of player edges.\033[0\n");
				return (1);
			}
			else if (y == file->y && y > 0 && map[file->y + 1] && ft_isspace(map[file->y + 1][file->x]))
			{
				printf("\033[0;34mError!\nCheck top of player edges.\033[0\n");
				return (1);
			}
			else if (y == file->y && y > 0 && x > 0 && ft_isspace(map[file->y][file->x - 1]))
			{
				printf("\033[0;34mError!\nCheck top of player edges.\033[0\n");
				return (1);
			}
			x++;
		}
		y++;
	}
	if (!map[y] || file->y == 0 || file->x == 0 || file->x == (int)(ft_strlen(map[file->y]) - 1))
	{
		printf("\033[0;34mError!\nPlayer on the edges.\033[0\n");
		return (1);
	}
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

int	ft_count_player(t_file *file, char **map)
{
	int	y;
	int	x;
	int	p;

	y = -1;
	p = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '\n')
				map[y][x] = ' ';
			if (valid_char(map[y][x]))
				return (printf("\033[0;34mError\nInvalid char in map!\033[0\n"));
			if (is_player(map[y][x]))
			{
				p++;
				file->y = y;
				file->x = x;
				file->orientation = map[y][x];
			}
		}
	}
	if (p == 1 && check_edges(file, map))
		return (1);
	else if (p != 1)
		return (printf("\033[0;34mError\nInvalid map! nº of players\033[0\n"));
	return (0);
}
