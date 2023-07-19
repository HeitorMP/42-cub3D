/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:33:21 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/19 12:15:03 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_values(t_root *game)
{
	int	i;

	i = 0;
	game->ray.side = 0;
	game->ray.hit = 0;
	game->moveSpeed = 0.08f;
	game->rotSpeed = 0.03f;
	while (i < 6)
	{
		game->keys[i] = 0;
		i++;
	}
	game->keys[6] = -1;
	game->keys[7] = 0;

	if (game->init_dir == 'N')
		init_north(game);
	else if (game->init_dir == 'S')
		init_south(game);
	else if (game->init_dir == 'W')
		init_west(game);
	else
		init_east(game);
}
