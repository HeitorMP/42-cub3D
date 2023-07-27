/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enemy_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:10:41 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/27 14:17:28 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

int	check_enemy(t_file *file, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < file->rows)
	{
		x = 0;
		while ((size_t)x < ft_strlen(map[y]))
		{
			if (map[y][x] == 'M')
			{
				file->has_enemy += 1;
				if (file->has_enemy > 1)
					return (printf("\033[0;34mError\n \
						Wrong number of enemy!\033[0\n"));
				file->enemy_x = x;
				file->enemy_y = y;
			}
			x++;
		}
		y++;
	}
	return (0);
}
