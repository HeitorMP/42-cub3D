/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:33:21 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/25 21:38:35 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	file_to_game(t_root *game, t_file *file)
{
	game->player.x_pos = (float)file->x + 0.5f;
	game->player.y_pos = (float)file->y + 0.5f;
	game->f_color = create_trgb(TRANSPARENCY, file->floor.red , file->floor.green, file->floor.blue); // receive from parse in the future
	game->c_color = create_trgb(TRANSPARENCY, file->ceilling.red, file->ceilling.green, file->ceilling.blue); // receive from parse in the future
	game->init_dir = file->orientaton; // receive from parse in the future
}

void	init_textures(t_root *game, t_file *file)
{
	game->background.addr = mlx_get_data_addr(game->background.img, &game->background.bits_per_pixel, &game->background.line_length, &game->background.endian);
	game->north_wall.img = mlx_xpm_file_to_image(game->mlx, file->no, &game->north_wall.w, &game->north_wall.h);
	game->north_wall.addr = mlx_get_data_addr(game->north_wall.img, &game->north_wall.bits_per_pixel, &game->north_wall.line_length, &game->north_wall.endian);
	
	game->south_wall.img = mlx_xpm_file_to_image(game->mlx, file->so, &game->south_wall.w, &game->south_wall.h);
	game->south_wall.addr = mlx_get_data_addr(game->south_wall.img, &game->south_wall.bits_per_pixel, &game->south_wall.line_length, &game->south_wall.endian);

	game->east_wall.img = mlx_xpm_file_to_image(game->mlx, file->ea, &game->east_wall.w, &game->east_wall.h);
	game->east_wall.addr = mlx_get_data_addr(game->east_wall.img, &game->east_wall.bits_per_pixel, &game->east_wall.line_length, &game->east_wall.endian);
	
	game->west_wall.img = mlx_xpm_file_to_image(game->mlx, file->we, &game->west_wall.w, &game->west_wall.h);
	game->west_wall.addr = mlx_get_data_addr(game->west_wall.img, &game->west_wall.bits_per_pixel, &game->west_wall.line_length, &game->west_wall.endian);
}

void	init_values(t_root *game, t_file *file)
{
	int	i;
	
	file_to_game(game, file);
	i = 0;
	game->ray.side = 0;
	game->ray.hit = 0;
	game->move_speed = 0.08f;
	game->rot_speed = 0.03f;
	while (i < 6)
	{
		game->keys[i] = 0;
		i++;
	}
	if (game->init_dir == 'N')
		init_north(game);
	else if (game->init_dir == 'S')
		init_south(game);
	else if (game->init_dir == 'W')
		init_west(game);
	else
		init_east(game);
}
