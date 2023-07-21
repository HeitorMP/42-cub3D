/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init_direction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:42:40 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/21 16:40:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_east(t_root *game)
{
	game->player.dir_x = 0.0f;
	game->player.dir_y = 1.0f;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

void	init_west(t_root *game)
{
	game->player.dir_x = 0.0f;
	game->player.dir_y = -1.0f;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

void	init_north(t_root *game)
{
	game->player.dir_x = -1.0f;
	game->player.dir_y = 0.0f;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

void	init_south(t_root *game)
{
	game->player.dir_x = 1.0f;
	game->player.dir_y = 0.0f;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}
