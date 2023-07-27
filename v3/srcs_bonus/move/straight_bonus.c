/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straight_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:36:35 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/27 10:12:47 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	move_forward(t_root *game)
{
	char	current;

	current = game->map[(int)(game->player.y_pos + \
		game->player.dir_x * MARGIN)][(int)game->player.x_pos];
	if (current == '0' || current == 'O' || current == ' ')
		game->player.y_pos += game->player.dir_x * game->move_speed;
	current = game->map[(int)(game->player.y_pos)][(int) \
		(game->player.x_pos + game->player.dir_y * MARGIN)];
	if (current == '0' || current == 'O' || current == ' ')
		game->player.x_pos += game->player.dir_y * game->move_speed;
}

void	move_backward(t_root *game)
{
	char	current;

	current = game->map[(int)(game->player.y_pos - \
		game->player.dir_x * MARGIN)][(int)game->player.x_pos];
	if (current == '0' || current == 'O' || current == ' ')
		game->player.y_pos -= game->player.dir_x * game->move_speed;
	current = game->map[(int)(game->player.y_pos)][(int) \
		(game->player.x_pos - game->player.dir_y * MARGIN)];
	if (current == '0' || current == 'O' || current == ' ')
		game->player.x_pos -= game->player.dir_y * game->move_speed;
}
