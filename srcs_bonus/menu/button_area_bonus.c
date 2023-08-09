/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_area_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:47:15 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/08 20:10:36 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	is_button1_area(int x, int y, t_root *game)
{
	if ((x > 380 && y > 200) && \
	(x < 380 + game->menu.button_h.w && y < 200 + game->menu.button_h.h))
		game->menu.is_area_b1 = 1;
	else
		game->menu.is_area_b1 = 0;
}

void	is_button2_area(int x, int y, t_root *game)
{
	if ((x > 380 && y > 300) && \
	(x < 380 + game->menu.button_h.w && y < 300 + game->menu.button_h.h))
		game->menu.is_area_b2 = 1;
	else
		game->menu.is_area_b2 = 0;
}

void	is_button3_area(int x, int y, t_root *game)
{
	if ((x > 450 && y > 400) && \
	(x < 450 + game->menu.button_q.w && y < 400 + game->menu.button_q.h))
		game->menu.is_area_b3 = 1;
	else
		game->menu.is_area_b3 = 0;
}
