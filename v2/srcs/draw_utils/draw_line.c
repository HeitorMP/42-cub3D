/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:21:40 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/19 10:23:11 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_line(t_root *root, t_coord begin, t_coord end, int color, void *win)
{
	t_sprite	temp;
	t_coord	new_begin;
	int		pixel;
	double deltaX;
	double deltaY;

	if (begin.x == end.x && begin.y == end.y)
		return ;
	new_begin = begin;
	if (end.x < begin.x)
	{
		new_begin = end;
		end = begin;
	}
	printf("begin: %d - %d | end: %d - %d\n", new_begin.x, new_begin.y, end.x, end.y);
	deltaX = end.x - new_begin.x;
	deltaY = end.y - new_begin.y;
	temp.img = mlx_new_image(root->mlx, IMGSIZE, IMGSIZE);
	temp.addr = mlx_get_data_addr(temp.img, &temp.bits_per_pixel, &temp.line_length,
								&temp.endian);
	pixel = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixel;
	deltaY /= pixel;

	double pixelX = new_begin.x;
	double pixelY = new_begin.y;
	while (pixel)
	{
		my_mlx_pixel_put(&temp, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixel;
	}
	put_draw_to_img(&root->mini_background, temp, 0, 0);
	mlx_put_image_to_window(root->mlx, win, root->mini_background.img, new_begin.x, new_begin.y);
}