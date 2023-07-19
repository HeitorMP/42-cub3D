/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:24:09 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/19 20:48:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_key(int keycode)
{
	return (keycode == UP || keycode == DOWN || \
			keycode == STRAFE_LEFT || keycode == STRAFE_RIGHT || \
			keycode == TURN_RIGHT || keycode == TURN_LEFT || keycode == F1);
}

int	input_release(int keycode, t_root *game)
{
	if (keycode == UP)
		game->keys[0] = 0;
	if (keycode == STRAFE_RIGHT)
		game->keys[1] = 0;
	if (keycode == DOWN)
		game->keys[2] = 0;
	if (keycode == STRAFE_LEFT)
		game->keys[3] = 0;
	if (keycode == TURN_RIGHT)
		game->keys[4] = 0;
	if (keycode == TURN_LEFT)
		game->keys[5] = 0;
	return (0);
}

int	input(int keycode, t_root *game)
{
	if (keycode == ESC)
		exit_game_request(game);
	else if (is_valid_key(keycode))
	{
		if (keycode == UP)
			game->keys[0] = 1;
		if (keycode == STRAFE_RIGHT)
			game->keys[1] = 1;
		if (keycode == DOWN)
			game->keys[2] = 1;
		if (keycode == STRAFE_LEFT)
			game->keys[3] = 1;
		if (keycode == TURN_RIGHT)
			game->keys[4] = 1;
		if (keycode == TURN_LEFT)
			game->keys[5] = 1;
		if (keycode == F1)
			game->keys[6] *= -1;
	}
	return (0);
}

int	mouse_input_release(int keycode, int x, int y, t_root *game)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		game->keys[7] = 0;
	return (0);
}

int	mouse_input(int keycode, int x, int y, t_root *game)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		game->keys[7] = 1;
	return (0);
}
