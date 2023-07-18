/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:24:26 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/18 15:56:23 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	exit_game_request(t_root *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);

	int i = -1;
	mlx_destroy_image(game->mlx, game->player.img);
	mlx_destroy_image(game->mlx, game->wall.img);
	mlx_destroy_image(game->mlx, game->bar.img);
	mlx_destroy_image(game->mlx, game->background.img);
	while (++i < 10)
		free(game->map[i]);
	free(game->map);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	printf("Good bye and thanks for playing!!\n");
	exit (0);
	return (1);
}