/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:58:39 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/07 12:10:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

int	is_door_near(t_root *game)
{
	if (game->map[(int)game->player.y_pos][(int)game->player.x_pos + 1] == 'D' \
	|| game->map[(int)game->player.y_pos][(int)game->player.x_pos + 1] == 'O')
		return (1);
	if (game->map[(int)game->player.y_pos][(int)game->player.x_pos - 1] == 'D' \
	|| game->map[(int)game->player.y_pos][(int)game->player.x_pos - 1] == 'O')
		return (2);
	if (game->map[(int)game->player.y_pos + 1][(int)game->player.x_pos] == 'D' \
	|| game->map[(int)game->player.y_pos + 1][(int)game->player.x_pos] == 'O')
		return (3);
	if (game->map[(int)game->player.y_pos - 1][(int)game->player.x_pos] == 'D' \
	|| game->map[(int)game->player.y_pos - 1][(int)game->player.x_pos] == 'O')
		return (4);
	return (0);
}

int	is_door_closed(t_root *game)
{
	if (game->map[(int)game->player.y_pos][(int)game->player.x_pos + 1] == 'D')
		return (1);
	if (game->map[(int)game->player.y_pos][(int)game->player.x_pos - 1] == 'D')
		return (1);
	if (game->map[(int)game->player.y_pos + 1][(int)game->player.x_pos] == 'D')
		return (1);
	if (game->map[(int)game->player.y_pos - 1][(int)game->player.x_pos] == 'D')
		return (1);
	return (0);
}

static void	set_open_door_to_map(t_root *game, int door_location)
{
	printf("%d\n", door_location);
	if (door_location == 1)
		game->map[(int)game->player.y_pos][(int)game->player.x_pos + 1] = 'O';
	else if (door_location == 2)
		game->map[(int)game->player.y_pos][(int)game->player.x_pos - 1] = 'O';
	else if (door_location == 3)
		game->map[(int)game->player.y_pos + 1][(int)game->player.x_pos] = 'O';
	else if (door_location == 4)
		game->map[(int)game->player.y_pos - 1][(int)game->player.x_pos] = 'O';
}

static void	set_close_door_to_map(t_root *game, int door_location)
{
	printf("%d\n", door_location);
	if (door_location == 1)
		game->map[(int)game->player.y_pos][(int)game->player.x_pos + 1] = 'D';
	else if (door_location == 2)
		game->map[(int)game->player.y_pos][(int)game->player.x_pos - 1] = 'D';
	else if (door_location == 3)
		game->map[(int)game->player.y_pos + 1][(int)game->player.x_pos] = 'D';
	else if (door_location == 4)
		game->map[(int)game->player.y_pos - 1][(int)game->player.x_pos] = 'D';
}

void	open_door(t_root *game)
{
	int	door_location;

	door_location = is_door_near(game);
	printf("location - %d\n", door_location);
	if (door_location != 0)
	{
		if (is_door_closed(game))
			set_open_door_to_map(game, door_location);
		else
			set_close_door_to_map(game, door_location);
	}
}
