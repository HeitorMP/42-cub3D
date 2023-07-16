/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:13:28 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/16 15:24:22 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static float	calc_wallX(t_root *game) {
	float	tmp_wallx;

	if (game->ray.side == 0)
		tmp_wallx = game->player.y_pos + game->ray.perpWallDist * game->ray.rayDirY;
	else
		tmp_wallx = game->player.x_pos + game->ray.perpWallDist * game->ray.rayDirX;
	
	tmp_wallx -= floor((tmp_wallx)); // convert float to smaller int;
	return (tmp_wallx);
}

void	draw_walls(t_root *game, int col)
{
	float wallX; //where exactly the wall was hit
	double step;
	double texPos;
	
	int texX;
	int texY;
	unsigned int color;
	int	y;
	
	wallX = calc_wallX(game);

	//x coordinate on the texture
	texX = (int)(wallX * (double)(64));
	if(game->ray.side == 0 && game->ray.rayDirX > 0)
		texX = 64 - texX - 1;
	if(game->ray.side == 1 && game->ray.rayDirY < 0)
		texX = 64 - texX - 1;

	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * 64 / game->calc.lineHeight; // 64 is the size of picture
	// Starting texture coordinate
	texPos = (game->calc.drawStart - 600 / 2 + game->calc.lineHeight / 2) * step;

	y = game->calc.drawStart;
	while (y < game->calc.drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		texY = (int)texPos & (64 - 1);
		texPos += step;
		color = get_pixel_img(game->wall, texX, texY);//texture[texNum][64 * texY + texX];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		//if(side == 1) color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&game->background, col, y, color);
		y++;
	}
}