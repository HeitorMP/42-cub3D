/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:32:05 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/06/08 18:54:23 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_mini_images(t_root *root, char **map, \
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
					floor, col * 20, line * 20);
			else if (map[line][col] == '1')
				put_img_to_img(&root->mini_background, \
					wall, col * 20, line * 20);
		}
		col = -1;
	}
}

void	draw_minimap(t_root *root, char **map)
{
	t_sprite	wall;
	t_sprite	floor;

	wall.img = mlx_xpm_file_to_image(root->mlx, "./assets/mini_greystone.xpm", \
		&wall.w, &wall.h);
	wall.addr = mlx_get_data_addr(wall.img, &wall.bits_per_pixel, \
		&wall.line_length, &wall.endian);
	floor.img = mlx_xpm_file_to_image(root->mlx, "./assets/mini_floor.xpm", \
		&floor.w, &floor.h);
	floor.addr = mlx_get_data_addr(floor.img, &floor.bits_per_pixel, \
		&floor.line_length, &floor.endian);
	put_mini_images(root, map, wall, floor);
	mlx_put_image_to_window(root->mlx, root->win2, \
		root->mini_background.img, 200, 200);
	mlx_destroy_image(root->mlx, wall.img);
	mlx_destroy_image(root->mlx, floor.img);
}
