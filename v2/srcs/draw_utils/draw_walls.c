/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:13:28 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/17 16:36:11 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static float	calc_wall_x(t_root *game)
{
	float	tmp_wallx;

	if (game->ray.side == 0)
		tmp_wallx = game->player.y_pos + \
		game->ray.perpWallDist * game->ray.rayDirY;
	else
		tmp_wallx = game->player.x_pos + game->ray.perpWallDist * \
		game->ray.rayDirX;
	tmp_wallx -= floor((tmp_wallx));
	return (tmp_wallx);
}

void	draw_walls(t_root *game, int col)
{
	float			wallx;
	double			texpos;
	int				tex_x;
	int				tex_y;
	int				y;

	wallx = calc_wall_x(game);
	tex_x = (int)(wallx * (double)(64));
	texpos = (game->calc.drawStart - 600 / 2 + game->calc.lineHeight / 2) \
		* (1.0 * 64 / game->calc.lineHeight);
	y = game->calc.drawStart;
	while (y < game->calc.drawEnd)
	{
		tex_y = (int)texpos & (64 - 1);
		texpos += (1.0 * 64 / game->calc.lineHeight);
		my_mlx_pixel_put(&game->background, col, y, \
			get_pixel_img(game->wall, tex_x, tex_y));
		y++;
	}
}
