/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:39:05 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/19 20:43:22 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_sprite(t_root *game)
{
	game->barrel.sprite_distance = ((game->player.x_pos - game->barrel.x_pos) * (game->player.x_pos - game->barrel.x_pos) + (game->player.y_pos - game->barrel.y_pos) * (game->player.y_pos - game->barrel.y_pos));
	double spriteX = game->barrel.x_pos - game->player.x_pos;
	double spriteY = game->barrel.y_pos - game->player.y_pos;
	double invDet = 1.0 / (game->player.plane_x *  game->player.dir_y - game->player.dir_x * game->player.plane_y); //required for correct matrix multiplication

	double transformX = invDet * (game->player.dir_y * spriteX - game->player.dir_x * spriteY);
	double transformY = invDet * (-game->player.plane_y * spriteX + game->player.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
	int spriteScreenX = (int)((SCREENWIDTH / 2) * (1 + transformX / transformY));

	//calculate height of the sprite on screen
	int spriteHeight = abs((int)(SCREENHEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	int drawStartY = -spriteHeight / 2 + SCREENHEIGHT / 2;
	if(drawStartY < 0) drawStartY = 0;
	int drawEndY = spriteHeight / 2 + SCREENHEIGHT / 2;
	if(drawEndY >= SCREENHEIGHT) drawEndY = SCREENHEIGHT - 1;

	//calculate width of the sprite
	int spriteWidth = abs( (int)(SCREENHEIGHT / (transformY)));
	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if(drawStartX < 0) drawStartX = 0;
	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if(drawEndX >= SCREENWIDTH) drawEndX = SCREENWIDTH - 1;

	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * IMGSIZE / spriteWidth) / 256;
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if(transformY > 0 && stripe > 0 && stripe < SCREENWIDTH && transformY < game->barrel.ZBuffer[stripe])
		for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
		{
			int d = (y) * 256 - SCREENHEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
			int texY = ((d * IMGSIZE) / spriteHeight) / 256;
			my_mlx_pixel_put(&game->background, stripe, y, get_pixel_img(game->barrel, texX, texY));
			//unsigned color = texture[sprite[spriteOrder[i]].texture][IMGSIZE * texY + texX]; //get current color from the texture
			//if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
		}
	}
}