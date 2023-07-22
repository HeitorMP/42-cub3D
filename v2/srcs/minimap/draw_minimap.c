/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:16:40 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/22 17:12:25 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap(t_root *game)
{
	int	line;
	int	col;

	col = 0;
	line = 0;
	while (line < 10)
	{
		while (col < 10)
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
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
}
