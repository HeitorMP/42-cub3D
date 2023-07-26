/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:18:43 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/26 13:47:03 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*calc_wallulate ray position and direction */
/* which box of the map we're in */
/* game->calc_dda.camera_x = 2 * game->x / (float)(SCREENWIDTH) - 1; 
   x-coordinate in camera space  -1 to correct view */
void	init_dda_values(t_root *game)
{
	game->calc_dda.camera_x = 2 * game->x / (float)(SCREENWIDTH) - 1; 
	game->ray.ray_dir_x = game->player.dir_x + \
		game->player.plane_x * game->calc_dda.camera_x;
	game->ray.ray_dir_y = game->player.dir_y + \
		game->player.plane_y * game->calc_dda.camera_x;
	printf("dda pos %f - %f\n", game->player.y_pos, game->player.x_pos);
	game->calc_dda.map_x = (int)(game->player.y_pos);
	game->calc_dda.map_y = (int)(game->player.x_pos);
	game->ray.hit = 0;
}

/*  length of ray from current position to next x or y-sid
	length of ray from one x or y-side to next x or y-side */
void	lenght_of_ray(t_root *game)
{
	if (game->ray.ray_dir_x == 0)
		game->ray.delta_dist_x = MAX_VALUE;
	else
		game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	if (game->ray.ray_dir_y == 0)
		game->ray.delta_dist_y = MAX_VALUE;
	else
		game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
}

/* calculate step and initial sideDist */
void	calculate_step(t_root *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.y_pos - \
			game->calc_dda.map_x) * game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->calc_dda.map_x + 1.0 - \
			game->player.y_pos) * game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.x_pos - \
			game->calc_dda.map_y) * game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->calc_dda.map_y + 1.0 - \
			game->player.x_pos) * game->ray.delta_dist_y;
	}
}

void	jump_next_square(t_root *game)
{
	if (game->ray.side_dist_x < game->ray.side_dist_y)
	{
		game->ray.side_dist_x += game->ray.delta_dist_x;
		game->calc_dda.map_x += game->ray.step_x;
		game->ray.side = 0;
	}
	else
	{
		game->ray.side_dist_y += game->ray.delta_dist_y;
		game->calc_dda.map_y += game->ray.step_y;
		game->ray.side = 1;
	}
}
