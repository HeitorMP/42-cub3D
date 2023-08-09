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

static const char	*trim_end(const char *str)
{
	const char	*end;

	if (!str)
		return (NULL);
	end = NULL;
	end = str;
	while (*end)
		end++;
	while (end > str && ft_isspace(*(end - 1)))
		end--;
	return (end);
}

char	*ft_trim_end(const char *str)
{
	int		i;
	int		size;
	char	*result;

	result = NULL;
	size = trim_end(str) - str;
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

/*y corresponde às linhas eixo y ; x às colunas eixo x*/
static int	check_player(int p, t_file *file, char **map)
{
	if (p == 1 && check_edges(file, map))
		return (1);
	else if (p != 1)
		return (printf("\033[0;34mError\nInvalid map! Nº of players\033[0\n"));
	return (0);
}

int	ft_count_player(t_file *file, char **map)
{
	int		y;
	int		x;
	int		p;

	y = -1;
	p = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
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
	if (check_player(p, file, map))
		return (1);
	return (0);
}
