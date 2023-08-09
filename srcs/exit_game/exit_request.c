/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:24:26 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/26 21:03:56 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_array(char **array)
{
	int	y;

	y = -1;
	if (array)
	{
		while (array[++y])
			free(array[y]);
		free(array);
	}
}

void	free_file(t_root *game)
{
	free_array(game->file->map);
	free(game->file->so);
	free(game->file->no);
	free(game->file->we);
	free(game->file->ea);
}

int	exit_game_request(t_root *game)
{
	free_file(game);
	free_array(game->map);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->north_wall.img);
	mlx_destroy_image(game->mlx, game->south_wall.img);
	mlx_destroy_image(game->mlx, game->east_wall.img);
	mlx_destroy_image(game->mlx, game->west_wall.img);
	mlx_destroy_image(game->mlx, game->background.img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	printf("Good bye and thanks for playing!!\n");
	exit (0);
	return (1);
}
