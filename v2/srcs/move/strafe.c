/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:55:02 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/16 11:59:53 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	strafe_right(t_root *game)
{
	if(game->map[(int)(game->player.x_pos + game->player.plane_x * 0.1f)][(int)game->player.y_pos] == '0')
				game->player.x_pos += game->player.plane_x * game->moveSpeed;
	if(game->map[(int)(game->player.x_pos)][(int)(game->player.y_pos + game->player.plane_y * 0.1f)] == '0')
		game->player.y_pos += game->player.plane_y * game->moveSpeed;
}

void	strafe_left(t_root *game)
{
	if(game->map[(int)(game->player.x_pos - game->player.plane_x * 0.1f)][(int)game->player.y_pos] == '0')
		game->player.x_pos -= game->player.plane_x * game->moveSpeed;
	if(game->map[(int)(game->player.x_pos)][(int)(game->player.y_pos - game->player.plane_y * 0.1f)] == '0')
		game->player.y_pos -= game->player.plane_y * game->moveSpeed;
}