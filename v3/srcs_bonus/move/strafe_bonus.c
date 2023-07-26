/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:55:02 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/23 16:32:14 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	strafe_right(t_root *game)
{
	char	current;

	current = game->map[(int)(game->player.y_pos + \
	game->player.plane_x * 0.1f)][(int)game->player.x_pos];
	if (current == '0' || current == 'O')
		game->player.y_pos += game->player.plane_x * game->move_speed;
	current = game->map[(int)(game->player.y_pos)][(int) \
		(game->player.x_pos + game->player.plane_y * 0.1f)];
	if (current == '0' || current == 'O')
		game->player.x_pos += game->player.plane_y * game->move_speed;
}

void	strafe_left(t_root *game)
{
	char	current;

	current = game->map[(int)(game->player.y_pos - \
		game->player.plane_x * 0.1f)][(int)game->player.x_pos];
	if (current == '0' || current == 'O')
		game->player.y_pos -= game->player.plane_x * game->move_speed;
	current = game->map[(int)(game->player.y_pos)][(int) \
		(game->player.x_pos - game->player.plane_y * 0.1f)];
	if (current == '0' || current == 'O')
		game->player.x_pos -= game->player.plane_y * game->move_speed;
}
