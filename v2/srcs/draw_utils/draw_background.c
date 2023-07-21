/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:18:45 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/21 11:56:33 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_back(t_root *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < SCREENHEIGHT)
	{
		while (x < SCREENWIDTH)
		{
			if (y < SCREENHEIGHT / 2)
				my_mlx_pixel_put(&game->background, x, y, game->c_color);
			else
				my_mlx_pixel_put(&game->background, x, y, game->f_color);
			x++;
		}
		x = 0;
		y++;
	}
}
