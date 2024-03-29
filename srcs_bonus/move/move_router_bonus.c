/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_router_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:39:34 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/23 16:32:10 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	move_player(t_root *game)
{
	if (game->keys[0])
		move_forward(game);
	if (game->keys[1])
		strafe_right(game);
	if (game->keys[2])
		move_backward(game);
	if (game->keys[3])
		strafe_left(game);
	if (game->keys[4])
		turn_right(game);
	if (game->keys[5])
		turn_left(game);
}
