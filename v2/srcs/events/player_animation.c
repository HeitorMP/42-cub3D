/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:36:36 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/19 20:38:03 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	player_animation(t_root *game)
{
	static int count_anim;
	
	if (count_anim >= 20)
		count_anim = 0;
	
	if (game->keys[7] == 0 && count_anim == 0)
	{
		game->player.img = mlx_xpm_file_to_image(game->mlx, "./assets/gun.xpm", &game->player.w, &game->player.h);
		game->player.addr = mlx_get_data_addr(game->player.img, &game->player.bits_per_pixel, &game->player.line_length, &game->player.endian);
		return ;
	}
	count_anim++;
	if (count_anim == 1)
	{
		game->player.img = mlx_xpm_file_to_image(game->mlx, "./assets/gun2.xpm", &game->player.w, &game->player.h);
		game->player.addr = mlx_get_data_addr(game->player.img, &game->player.bits_per_pixel, &game->player.line_length, &game->player.endian);
	}
	else if (count_anim == 11)
	{
		game->player.img = mlx_xpm_file_to_image(game->mlx, "./assets/gun3.xpm", &game->player.w, &game->player.h);
		game->player.addr = mlx_get_data_addr(game->player.img, &game->player.bits_per_pixel, &game->player.line_length, &game->player.endian);
	}
}