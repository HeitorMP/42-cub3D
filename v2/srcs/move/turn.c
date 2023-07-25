/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:31:12 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/25 21:07:35 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	turn_left(t_root *game)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * \
		cos(game->rot_speed) - game->player.dir_y * sin(game->rot_speed);
	game->player.dir_y = old_dir_x * sin(game->rot_speed) \
		+ game->player.dir_y * cos(game->rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * \
		cos(game->rot_speed) - game->player.plane_y * sin(game->rot_speed);
	game->player.plane_y = old_plane_x * sin(game->rot_speed) \
		+ game->player.plane_y * cos(game->rot_speed);
}

void	turn_right(t_root *game)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * \
		cos(-game->rot_speed) - game->player.dir_y * sin(-game->rot_speed);
	game->player.dir_y = old_dir_x * sin(-game->rot_speed) \
		+ game->player.dir_y * cos(-game->rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * \
		cos(-game->rot_speed) - game->player.plane_y * sin(-game->rot_speed);
	game->player.plane_y = old_plane_x * sin(-game->rot_speed) \
		+ game->player.plane_y * cos(-game->rot_speed);
}
