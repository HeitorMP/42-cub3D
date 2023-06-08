/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_miniplayer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:33:21 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/06/08 18:54:30 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_mini_player(t_root *root)
{
	int	line;
	int	col;

	line = -1;
	col = -1;
	while (++line < 10)
	{
		while (++col < 10)
			my_mlx_pixel_put(&root->player, col, line, 0x0000FF00);
		col = -1;
	}
	mlx_put_image_to_window(root->mlx, root->win2, root->player.img, \
		root->player.x_pos, root->player.y_pos);
}
