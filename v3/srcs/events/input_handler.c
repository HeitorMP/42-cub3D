/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:24:09 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/26 20:53:55 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_key(int keycode)
{
	return (keycode == W_KEY || keycode == S_KEY || \
			keycode == A_KEY || keycode == D_KEY || \
			keycode == ARROW_RIGHT_KEY || keycode == ARROW_LEFT_KEY);
}

int	input_release(int keycode, t_root *game)
{
	if (keycode == W_KEY)
		game->keys[UP] = 0;
	if (keycode == D_KEY)
		game->keys[STRAFE_RIGHT] = 0;
	if (keycode == S_KEY)
		game->keys[DOWN] = 0;
	if (keycode == A_KEY)
		game->keys[STRAFE_LEFT] = 0;
	if (keycode == ARROW_RIGHT_KEY)
		game->keys[TURN_RIGHT] = 0;
	if (keycode == ARROW_LEFT_KEY)
		game->keys[TURN_LEFT] = 0;
	return (0);
}

int	input(int keycode, t_root *game)
{
	if (keycode == ESC)
		exit_game_request(game);
	else if (is_valid_key(keycode))
	{
		if (keycode == W_KEY)
			game->keys[UP] = 1;
		if (keycode == D_KEY)
			game->keys[STRAFE_RIGHT] = 1;
		if (keycode == S_KEY)
			game->keys[DOWN] = 1;
		if (keycode == A_KEY)
			game->keys[STRAFE_LEFT] = 1;
		if (keycode == ARROW_RIGHT_KEY)
			game->keys[TURN_RIGHT] = 1;
		if (keycode == ARROW_LEFT_KEY)
			game->keys[TURN_LEFT] = 1;
	}
	return (0);
}
