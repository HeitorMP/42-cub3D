/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:43:23 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/08 19:48:58 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	set_image(t_root *game, t_sprite *sprite, char *path)
{
	mlx_destroy_image(game->mlx, sprite->img);
	sprite->img = mlx_xpm_file_to_image(game->mlx, path, \
		&sprite->w, &sprite->h);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel, \
		&sprite->line_length, &sprite->endian);
}
