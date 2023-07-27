/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:54:32 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/27 14:14:36 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

static void	init_mini_map_textures(t_root *game)
{
	game->mini_player.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/mini_player.xpm", &game->mini_player.w, &game->mini_player.h);
	game->mini_player.addr = mlx_get_data_addr(game->mini_player.img, \
		&game->mini_player.bits_per_pixel, &game->mini_player.line_length, \
		&game->mini_player.endian);
	game->mini_door.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/mini_door.xpm", &game->mini_door.w, &game->mini_door.h);
	game->mini_door.addr = mlx_get_data_addr(game->mini_door.img, \
		&game->mini_door.bits_per_pixel, &game->mini_door.line_length, \
		&game->mini_door.endian);
	game->mini_wall.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/mini_wall.xpm", &game->mini_wall.w, &game->mini_wall.h);
	game->mini_wall.addr = mlx_get_data_addr(game->mini_wall.img, \
	&game->mini_wall.bits_per_pixel, &game->mini_wall.line_length, \
		&game->mini_wall.endian);
}

static void	init_bonus_textures(t_root *game)
{
	game->background.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->background.addr = mlx_get_data_addr(game->background.img, \
		&game->background.bits_per_pixel, &game->background.line_length, \
		&game->background.endian);
	game->door.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/door.xpm", &game->door.w, &game->door.h);
	game->door.addr = mlx_get_data_addr(game->door.img, \
	&game->door.bits_per_pixel, &game->door.line_length, &game->door.endian);
	game->bar.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/hbar.xpm", &game->bar.w, &game->bar.h);
	game->bar.addr = mlx_get_data_addr(game->bar.img, \
		&game->bar.bits_per_pixel, &game->bar.line_length, &game->bar.endian);
	game->player.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/gun.xpm", &game->player.w, &game->player.h);
	game->player.addr = mlx_get_data_addr(game->player.img, \
		&game->player.bits_per_pixel, \
		&game->player.line_length, &game->player.endian);
	game->barrel.img = mlx_xpm_file_to_image(game->mlx, \
		"./assets/barrel.xpm", &game->barrel.w, &game->barrel.h);
	game->barrel.addr = mlx_get_data_addr(game->barrel.img, \
		&game->barrel.bits_per_pixel, &game->barrel.line_length, \
		&game->barrel.endian);
}

void	init_textures(t_root *game, t_file *file)
{
	init_bonus_textures(game);
	init_mini_map_textures(game);
	game->north_wall.img = mlx_xpm_file_to_image(game->mlx, file->no, \
		&game->north_wall.w, &game->north_wall.h);
	game->north_wall.addr = mlx_get_data_addr(game->north_wall.img, \
		&game->north_wall.bits_per_pixel, &game->north_wall.line_length, \
		&game->north_wall.endian);
	game->south_wall.img = mlx_xpm_file_to_image(game->mlx, file->so, \
		&game->south_wall.w, &game->south_wall.h);
	game->south_wall.addr = mlx_get_data_addr(game->south_wall.img, \
		&game->south_wall.bits_per_pixel, &game->south_wall.line_length, \
		&game->south_wall.endian);
	game->east_wall.img = mlx_xpm_file_to_image(game->mlx, file->ea, \
		&game->east_wall.w, &game->east_wall.h);
	game->east_wall.addr = mlx_get_data_addr(game->east_wall.img, \
		&game->east_wall.bits_per_pixel, &game->east_wall.line_length, \
		&game->east_wall.endian);
	game->west_wall.img = mlx_xpm_file_to_image(game->mlx, file->we, \
		&game->west_wall.w, &game->west_wall.h);
	game->west_wall.addr = mlx_get_data_addr(game->west_wall.img, \
		&game->west_wall.bits_per_pixel, &game->west_wall.line_length, \
		&game->west_wall.endian);
}
