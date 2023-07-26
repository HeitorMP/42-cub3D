/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:31:08 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/24 03:31:08 by nmoreira         ###   ########.fr       */
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

int checkmap(char **map, int x, int y)
{
    int result = 0;
    
    // Verificação original para espaços em branco ou '1' na posição atual
    if (map[y][x] != ' ' && map[y][x] != '1')
        return 1;
    map[y][x] = 'A';

    // Verificar limites do mapa antes de fazer chamadas recursivas
    if (map[y][x + 1] && map[y][x + 1] == ' ')
        return 1;
    if (map[y + 1] && ((int)ft_strlen(map[y + 1]) < x || map[y + 1][x] == ' '))
        return 1;
    if (x - 1 >= 0 && map[y][x - 1] && map[y][x - 1] == ' ')
        return 1;
    if (y - 1 >= 0 && ((int)ft_strlen(map[y - 1]) < x || map[y - 1][x] == ' '))
        return 1;

    // Verificar todas as direções adjacentes recursivamente
    if (map[y][x + 1] && (map[y][x + 1] == '1' || map[y][x + 1] == 'D'))
        result += checkmap(map, x + 1, y);
    if (map[y + 1] && (int)ft_strlen(map[y + 1]) > x && (map[y + 1][x] == '1' || map[y + 1][x] == 'D'))
        result += checkmap(map, x, y + 1);
    if (y - 1 >= 0 && (int)ft_strlen(map[y - 1]) > x && (map[y - 1][x] == '1' || map[y - 1][x] == 'D'))
        result += checkmap(map, x, y - 1);
    if (x - 1 >= 0 && map[y][x - 1] && (map[y][x - 1] == '1' || map[y][x - 1] == 'D'))
        result += checkmap(map, x - 1, y);

    return result;
}
