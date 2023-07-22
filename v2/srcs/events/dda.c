/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:51:18 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/22 16:20:01 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* While no hit do step */
/* if hit something different of 0 hit = 1 */
static void	check_hit(t_root *game)
{
	char	current;

	current = 0;
	while (game->ray.hit == 0)
	{
		jump_next_square(game);
		current = game->map[game->calc_dda.map_x][game->calc_dda.map_y];
		if (current == '1' || current == 'D')
			game->ray.hit = 1;
	}
}

/* Calculate distance projected on camera direction 
	(Euclidean distance would give fisheye effect!) */
static void	calculate_distance(t_root *game)
{
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.side_dist_x \
			- game->ray.delta_dist_x);
	else
		game->ray.perp_wall_dist = (game->ray.side_dist_y \
			- game->ray.delta_dist_y);
}

void	dda_calculation(t_root *game)
{
	game->x = 0;
	while (game->x < SCREENWIDTH)
	{
		init_dda_values(game);
		lenght_of_ray(game);
		calculate_step(game);
		check_hit(game);
		calculate_distance(game);
		game->calc_wall.line_height = \
			(int)(SCREENHEIGHT / game->ray.perp_wall_dist);
		game->calc_wall.draw_start = \
			(game->calc_wall.line_height * -1) / 2 + SCREENHEIGHT / 2;
		if (game->calc_wall.draw_start < 0)
			game->calc_wall.draw_start = 0;
		game->calc_wall.draw_end = \
			game->calc_wall.line_height / 2 + SCREENHEIGHT / 2;
		if (game->calc_wall.draw_end >= SCREENHEIGHT)
			game->calc_wall.draw_end = SCREENHEIGHT - 1;
		draw_walls(game, game->x);
		game->barrel.z_buffer[game->x] = game->ray.perp_wall_dist;
		game->x++;
	}
}
