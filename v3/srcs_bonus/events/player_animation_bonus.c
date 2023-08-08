/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:36:36 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/08 20:07:53 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	player_animation(t_root *game)
{
	static int	count_anim;

	if (count_anim >= 20)
		count_anim = 0;
	if (game->keys[7] == 0 && count_anim == 0)
	{
		set_image(game, &game->player, SHOOT1_XPM);
		return ;
	}
	count_anim++;
	if (count_anim == 1)
		set_image(game, &game->player, SHOOT2_XPM);
	else if (count_anim == 11)
		set_image(game, &game->player, SHOOT3_XPM);
}
