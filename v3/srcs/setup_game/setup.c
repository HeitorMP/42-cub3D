/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:33:21 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/07 09:43:28 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	copy_map(t_root *game, t_file *file)
{
	int	y;

	y = -1;
	game->map = malloc(sizeof(char *) * (file->rows + 1));
	while (++y < file->rows)
	{
		game->map[y] = ft_strdup_cub(file->map[y]);
	}
	game->map[y] = NULL;
}

static void	file_to_game(t_root *game, t_file *file)
{
	game->player.x_pos = (float)file->x + 0.5;
	game->player.y_pos = (float)file->y + 0.5;
	copy_map(game, file);
	game->map[(int)game->player.y_pos][(int)game->player.x_pos] = '0';
	game->f_color = create_trgb(TRANSPARENCY, file->floor.red, \
		file->floor.green, file->floor.blue);
	game->c_color = create_trgb(TRANSPARENCY, file->ceilling.red, \
		file->ceilling.green, file->ceilling.blue);
	game->init_dir = file->orientation;
	game->map_lines = file->rows;
	game->file = file;
}

void	init_textures(t_root *game, t_file *file)
{
	game->background.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	game->background.addr = mlx_get_data_addr(game->background.img, \
		&game->background.bits_per_pixel, &game->background.line_length, \
		&game->background.endian);
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

int	init_file(t_file *file)
{
	file->orientation = 0;
	file->ceilling.blue = -1;
	file->ceilling.green = -1;
	file->ceilling.red = -1;
	file->floor.red = -1;
	file->floor.green = -1;
	file->floor.blue = -1;
	file->rows = 0;
	file->x = -1;
	file->y = -1;
	file->x0 = -1;
	file->y0 = -1;
	file->no = NULL;
	file->so = NULL;
	file->we = NULL;
	file->ea = NULL;
	file->map = NULL;
	file->fd1 = -1;
	file->fd2 = -1;
	file->fd3 = -1;
	return (0);
}

void	init_values(t_root *game, t_file *file)
{
	int	i;

	i = 0;
	game->ray.side = 0;
	game->ray.hit = 0;
	game->move_speed = 0.08f;
	game->rot_speed = 0.03f;
	file_to_game(game, file);
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
