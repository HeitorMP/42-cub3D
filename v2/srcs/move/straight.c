/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:36:35 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/16 11:57:15 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_root *game)
{
	if(game->map[(int)(game->player.x_pos + game->player.dir_x * MARGIN)][(int)game->player.y_pos] == '0')
		game->player.x_pos += game->player.dir_x * game->moveSpeed;
	if(game->map[(int)(game->player.x_pos)][(int)(game->player.y_pos + game->player.dir_y * MARGIN)] == '0')
		game->player.y_pos += game->player.dir_y * game->moveSpeed;
}

void	move_backward(t_root *game)
{
	if(game->map[(int)(game->player.x_pos - game->player.dir_x * MARGIN)][(int)game->player.y_pos] == '0')
		game->player.x_pos -= game->player.dir_x * game->moveSpeed;
	if(game->map[(int)(game->player.x_pos)][(int)(game->player.y_pos - game->player.dir_y * MARGIN)] == '0')
		game->player.y_pos -= game->player.dir_y * game->moveSpeed;
}
