/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_router.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:39:34 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/25 21:10:41 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_player(t_root *game)
{
	if (game->keys[UP])
		move_forward(game);
	if (game->keys[STRAFE_RIGHT])
		strafe_right(game);
	if (game->keys[DOWN])
		move_backward(game);
	if (game->keys[STRAFE_LEFT])
		strafe_left(game);
	if (game->keys[TURN_RIGHT])
		turn_right(game);
	if (game->keys[TURN_LEFT])
		turn_left(game);
}
