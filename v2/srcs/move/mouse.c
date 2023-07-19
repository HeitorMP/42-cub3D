/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:25:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/19 12:14:19 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mouse_move(int x, int y, t_root *game)
{
	int			direction;
	static int	oldx;

	(void)y;
	direction = 2;

	if (oldx < SCREENWIDTH / 2)
		direction = 1;
	else if (oldx > SCREENWIDTH / 2)
		direction = 0;
	if (game->keys[6] == -1)
		direction = 2;

	if (direction == 1) {
		turn_left(game);
		direction = 2;
	}
	else if (direction == 0)
	{
		turn_right(game);
		direction = 2;
	}
	oldx = x;
	return (0);
}