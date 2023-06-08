/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:19:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/06/08 19:02:47 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_map_images(t_root *root, char **map, \
						t_sprite wall, t_sprite floor)
{
	int	line;
	int	col;

	line = -1;
	col = -1;
	while (++line < 5)
	{
		while (++col < 5)
		{
			if (map[line][col] == '0')
				put_img_to_img(&root->mini_background, \
					floor, col * 64, line * 64);
			else if (map[line][col] == '1')
				put_img_to_img(&root->mini_background, \
					wall, col * 64, line * 64);
		}
		col = -1;
	}
}

void	draw_2dmap(t_root *root, char **map)
{
	t_sprite	wall;
	t_sprite	floor;

	wall.img = mlx_xpm_file_to_image(root->mlx, "./assets/greystone.xpm", \
		&wall.w, &wall.h);
	wall.addr = mlx_get_data_addr(wall.img, &wall.bits_per_pixel, \
		&wall.line_length, &wall.endian);
	floor.img = mlx_xpm_file_to_image(root->mlx, "./assets/floor.xpm", \
		&floor.w, &floor.h);
	floor.addr = mlx_get_data_addr(floor.img, &floor.bits_per_pixel, \
		&floor.line_length, &floor.endian);
	put_map_images(root, map, wall, floor);
	mlx_put_image_to_window(root->mlx, root->win2, \
		root->mini_background.img, 0, 0);
	mlx_destroy_image(root->mlx, wall.img);
	mlx_destroy_image(root->mlx, floor.img);
}