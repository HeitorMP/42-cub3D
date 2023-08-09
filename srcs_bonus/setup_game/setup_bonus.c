/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:33:21 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/08 19:44:45 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

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
	if (file->has_enemy)
	{
		game->barrel.x_pos = file->enemy_x + 0.5;
		game->barrel.y_pos = file->enemy_y + 0.5;
	}
}

int	init_file(t_file *file)
{
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
	file->valid = 0;
	file->no = NULL;
	file->so = NULL;
	file->we = NULL;
	file->ea = NULL;
	file->map = NULL;
	file->fd1 = -1;
	file->fd2 = -1;
	file->fd3 = -1;
	file->has_enemy = 0;
	file->enemy_x = 0;
	file->enemy_y = 0;
	return (0);
}

static int	get_bigest_line(t_root *game)
{
	int		i;
	size_t	max;

	i = 0;
	max = 0;
	while (i < game->map_lines)
	{
		if (max < ft_strlen(game->map[i]))
			max = ft_strlen(game->map[i]);
		i++;
	}
	return ((int)max);
}

void	init_values(t_root *game, t_file *file)
{
	int	i;

	i = -1;
	game->ray.side = 0;
	game->ray.hit = 0;
	game->move_speed = 0.08f;
	game->rot_speed = 0.03f;
	game->menu.play = 0;
	game->menu.is_area_b1 = 0;
	game->menu.is_area_b2 = 0;
	game->menu.is_area_b3 = 0;
	file_to_game(game, file);
	game->map_lines = file->rows;
	game->map_cols = get_bigest_line(game);
	init_calc_structs(game);
	while (++i < 6)
		game->keys[i] = 0;
	game->keys[6] = -1;
	game->keys[7] = 0;
	game->keys[8] = 0;
	check_direction(game);
}
