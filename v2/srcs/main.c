/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/26 15:21:23 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	game_loop(t_root *game)
{
 	
	draw_back(game); // draw ceiling and floor
	dda_calculation(game);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	move_player(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_root	game;
	t_file	file;

	check_path(argc, argv);
	if (ft_parser(&file, argv[1]))
	{
		ft_free_sfile(&file);
		exit(1);
	}

	init_values(&game, &file);
	game.mlx = mlx_init();
	game.background.img = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	init_textures(&game, &file);
	game.win = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	mlx_hook(game.win, 02, (1L<<0), input, &game);
	mlx_hook(game.win, 03, (1L<<1), input_release, &game);
	mlx_hook(game.win, 17, 1L<<0, exit_game_request, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
