/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:33:21 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/23 16:43:04 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	init_values(t_root *game)
{
	int	i;

	i = 0;
	game->ray.side = 0;
	game->ray.hit = 0;
	game->move_speed = 0.09f;
	game->rot_speed = 0.04f;
	while (i < 6)
	{
		game->keys[i] = 0;
		i++;
	}
	game->keys[6] = -1;
	game->keys[7] = 0;
	game->keys[8] = 0;
	if (game->init_dir == 'N')
		init_north(game);
	else if (game->init_dir == 'S')
		init_south(game);
	else if (game->init_dir == 'W')
		init_west(game);
	else
		init_east(game);
}
