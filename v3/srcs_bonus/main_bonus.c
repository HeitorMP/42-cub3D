/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/08/08 20:07:41 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes_bonus/cub3d_bonus.h"

int	main_menu(t_root *game)
{
	put_img_to_img(&game->background, game->menu.menu_back, 0, 0);
	put_img_to_img(&game->background, game->menu.button_h, 380, 200);
	put_img_to_img(&game->background, game->menu.button_n, 380, 300);
	put_img_to_img(&game->background, game->menu.button_q, 450, 400);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	if (game->keys[7] == 1 && game->menu.is_area_b1)
		game->menu.play = 1;
	if (game->keys[7] == 1 && game->menu.is_area_b2)
	{
		mlx_destroy_image(game->mlx, game->bar.img);
		set_image(game, &game->bar, BAR_N_XPM);
		game->menu.play = 1;
	}
	if (game->keys[7] == 1 && game->menu.is_area_b3)
		exit_game_request(game);
	return (0);
}

int	game_loop(t_root *game)
{
	if (game->menu.play == 0)
		main_menu(game);
	else
	{
		draw_back(game);
		dda_calculation(game);
		check_mouse_lock(game);
		player_animation(game);
		if (game->file->has_enemy)
			draw_sprite(game);
		put_img_to_img(&game->background, game->bar, 0, 668);
		put_img_to_img(&game->background, game->player, 448, 539);
		mlx_put_image_to_window(game->mlx, game->win, \
			game->background.img, 0, 0);
		draw_minimap(game);
		move_player(game);
	}
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
	game.win = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	init_textures(&game, &file);
	mlx_hook(game.win, 02, 1L << 0, input, &game);
	mlx_hook(game.win, 03, 1L << 1, input_release, &game);
	mlx_hook(game.win, 17, 1L << 0, exit_game_request, &game);
	mlx_hook(game.win, 04, 1L << 2, mouse_input, &game);
	mlx_hook(game.win, 05, 1L << 3, mouse_input_release, &game);
	mlx_hook(game.win, 06, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
