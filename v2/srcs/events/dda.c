/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:51:18 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/19 20:52:31 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	dda_calculation(t_root *game)
{
	for(int x = 0; x < SCREENWIDTH; x++) // x = size of columns in windows
		{
			//calculate ray position and direction
			float cameraX = 2 * x / (float)(SCREENWIDTH) - 1; //x-coordinate in camera space // -1 to correct view
			game->ray.rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
			game->ray.rayDirY = game->player.dir_y + game->player.plane_y * cameraX;

			//which box of the map we're in
			int mapX = (int)(game->player.x_pos);
			int mapY = (int)(game->player.y_pos);

			//length of ray from current position to next x or y-sid
			//length of ray from one x or y-side to next x or y-side
			if (game->ray.rayDirX == 0)
			{
				game->ray.deltaDistX = 1e30;
			}
			else
			{
				game->ray.deltaDistX = fabs(1 / game->ray.rayDirX);
			}
			game->ray.deltaDistY = (game->ray.rayDirY == 0) ? 1e30 : fabs(1 / game->ray.rayDirY);
			game->ray.hit = 0;
			if (game->ray.rayDirX < 0)
			{
				game->ray.stepX = -1;
				game->ray.sideDistX = (game->player.x_pos - mapX) * game->ray.deltaDistX;
			}
			else
			{
				game->ray.stepX = 1;
				game->ray.sideDistX = (mapX + 1.0 - game->player.x_pos) * game->ray.deltaDistX;
			}
			if (game->ray.rayDirY < 0)
			{
				game->ray.stepY = -1;
				game->ray.sideDistY = (game->player.y_pos - mapY) * game->ray.deltaDistY;
			}
			else
			{
				game->ray.stepY = 1;
				game->ray.sideDistY = (mapY + 1.0 - game->player.y_pos) * game->ray.deltaDistY;
			}
			while (game->ray.hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (game->ray.sideDistX < game->ray.sideDistY)
				{
					game->ray.sideDistX += game->ray.deltaDistX;
					mapX += game->ray.stepX;
					game->ray.side = 0;
				}
				else
				{
					game->ray.sideDistY += game->ray.deltaDistY;
					mapY += game->ray.stepY;
					game->ray.side = 1;
				}
				//Check if ray has hit a wall
				if (game->map[mapX][mapY] != '0')
					game->ray.hit = 1;
			}
			if(game->ray.side == 0)
				game->ray.perpWallDist = (game->ray.sideDistX - game->ray.deltaDistX);
			else
				game->ray.perpWallDist = (game->ray.sideDistY - game->ray.deltaDistY);

			game->calc.lineHeight = (int)(SCREENHEIGHT / game->ray.perpWallDist);
			game->calc.drawStart = (game->calc.lineHeight * -1) / 2 + SCREENHEIGHT / 2;
			if(game->calc.drawStart < 0)
				game->calc.drawStart = 0;
			game->calc.drawEnd = game->calc.lineHeight / 2 + SCREENHEIGHT / 2;
			if(game->calc.drawEnd >= SCREENHEIGHT)
				game->calc.drawEnd = SCREENHEIGHT - 1;

			//******************** DESENHA APENAS NAS PAREDES *****************************
			draw_walls(game, x);
			game->barrel.ZBuffer[x] = game->ray.perpWallDist;
		}
}