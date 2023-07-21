/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:36:36 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/21 11:42:20 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	no_shoot_sprite(t_root *game)
{
	mlx_destroy_image(game->mlx, game->player.img);
	game->player.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/gun.xpm", &game->player.w, &game->player.h);
	game->player.addr = mlx_get_data_addr(game->player.img, \
	&game->player.bits_per_pixel, &game->player.line_length, \
	&game->player.endian);
}

static void	shoot_sprite1(t_root *game)
{
	mlx_destroy_image(game->mlx, game->player.img);
	game->player.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/gun2.xpm", &game->player.w, &game->player.h);
	game->player.addr = mlx_get_data_addr(game->player.img, \
		&game->player.bits_per_pixel, &game->player.line_length, \
		&game->player.endian);
}

static void	shoot_sprite2(t_root *game)
{
	mlx_destroy_image(game->mlx, game->player.img);
	game->player.img = mlx_xpm_file_to_image(game->mlx, \
	"./assets/gun3.xpm", &game->player.w, &game->player.h);
	game->player.addr = mlx_get_data_addr(game->player.img, \
	&game->player.bits_per_pixel, &game->player.line_length, \
	&game->player.endian);
}

void	player_animation(t_root *game)
{
	static int	count_anim;

	if (count_anim >= 20)
		count_anim = 0;
	if (game->keys[7] == 0 && count_anim == 0)
	{
		no_shoot_sprite(game);
		return ;
	}
	count_anim++;
	if (count_anim == 1)
		shoot_sprite1(game);
	else if (count_anim == 11)
		shoot_sprite2(game);
}
