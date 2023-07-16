/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:31:12 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/16 12:07:41 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	turn_left(t_root *game)
{
	float oldDirX;
	float oldPlaneX;
	
	oldDirX = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(game->rotSpeed) - game->player.dir_y * sin(game->rotSpeed);
	game->player.dir_y = oldDirX * sin(game->rotSpeed) + game->player.dir_y * cos(game->rotSpeed);
	oldPlaneX = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(game->rotSpeed) - game->player.plane_y * sin(game->rotSpeed);
	game->player.plane_y = oldPlaneX * sin(game->rotSpeed) + game->player.plane_y * cos(game->rotSpeed);
}

void	turn_right(t_root *game)
{
	float oldDirX;
	float oldPlaneX;

	oldDirX = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-game->rotSpeed) - game->player.dir_y * sin(-game->rotSpeed);
	game->player.dir_y = oldDirX * sin(-game->rotSpeed) + game->player.dir_y * cos(-game->rotSpeed);
	oldPlaneX = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-game->rotSpeed) - game->player.plane_y * sin(-game->rotSpeed);
	game->player.plane_y = oldPlaneX * sin(-game->rotSpeed) + game->player.plane_y * cos(-game->rotSpeed);
}
