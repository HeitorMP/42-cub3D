/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_request_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:24:26 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/08 19:15:37 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

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

static void	free_images(t_root *game)
{
	mlx_destroy_image(game->mlx, game->north_wall.img);
	mlx_destroy_image(game->mlx, game->south_wall.img);
	mlx_destroy_image(game->mlx, game->east_wall.img);
	mlx_destroy_image(game->mlx, game->west_wall.img);
	mlx_destroy_image(game->mlx, game->background.img);
	mlx_destroy_image(game->mlx, game->bar.img);
	mlx_destroy_image(game->mlx, game->door.img);
	mlx_destroy_image(game->mlx, game->barrel.img);
	mlx_destroy_image(game->mlx, game->player.img);
	mlx_destroy_image(game->mlx, game->mini_door.img);
	mlx_destroy_image(game->mlx, game->mini_player.img);
	mlx_destroy_image(game->mlx, game->mini_wall.img);
}

static void	free_menu(t_root *game)
{
	mlx_destroy_image(game->mlx, game->menu.button_h.img);
	mlx_destroy_image(game->mlx, game->menu.button_n.img);
	mlx_destroy_image(game->mlx, game->menu.button_q.img);
	mlx_destroy_image(game->mlx, game->menu.menu_back.img);
}

int	exit_game_request(t_root *game)
{
	free_file(game);
	free_array(game->map);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	free_images(game);
	free_menu(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	printf("Good bye and thanks for playing!!\n");
	exit (0);
	return (1);
}
