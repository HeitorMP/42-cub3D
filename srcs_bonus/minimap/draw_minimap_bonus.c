/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:16:40 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/27 19:49:40 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	draw_minimap(t_root *game)
{
	int		line;
	int		col;

	col = 0;
	line = 0;
	while (line < game->map_lines)
	{
		while (col < (int)ft_strlen(game->map[line]))
		{
			if (game->map[line][col] == '1')
				put_img_to_img(&game->background, game->mini_wall, \
					col * 10, line * 10);
			else if (game->map[line][col] == 'D')
				put_img_to_img(&game->background, game->mini_door, \
					col * 10, line * 10);
			col++;
		}
		col = 0;
		line++;
	}
	put_img_to_img(&game->background, game->mini_player, \
		(int)game->player.x_pos * 10, (int)game->player.y_pos * 10);
}
