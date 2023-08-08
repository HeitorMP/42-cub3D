/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:25:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/08 19:50:49 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

static void	in_game_mouse_move(int x, t_root *game)
{
	int			direction;
	static int	oldx;

	direction = 2;
	if (oldx < SCREENWIDTH / 2)
		direction = 1;
	else if (oldx > SCREENWIDTH / 2)
		direction = 0;
	if (game->keys[6] == -1)
		direction = 2;
	if (direction == 1)
	{
		turn_left(game);
		direction = 2;
	}
	else if (direction == 0)
	{
		turn_right(game);
		direction = 2;
	}
	oldx = x;
}

static void	in_menu_mouse_move(int x, int y, t_root *game)
{
	is_button1_area(x, y, game);
	is_button2_area(x, y, game);
	is_button3_area(x, y, game);
	if (game->menu.is_area_b1)
		set_image(game, &game->menu.button_h, BUTTON1_SELECTED_XPM);
	else
		set_image(game, &game->menu.button_h, BUTTON1_XPM);
	if (game->menu.is_area_b2)
		set_image(game, &game->menu.button_n, BUTTON2_SELECTED_XPM);
	else
		set_image(game, &game->menu.button_n, BUTTON2_XPM);
	if (game->menu.is_area_b3)
		set_image(game, &game->menu.button_q, BUTTON3_SELECTED_XPM);
	else
		set_image(game, &game->menu.button_q, BUTTON3_XPM);
}

int	mouse_move(int x, int y, t_root *game)
{
	if (game->menu.play)
		in_game_mouse_move(x, game);
	else
		in_menu_mouse_move(x, y, game);
	return (0);
}
