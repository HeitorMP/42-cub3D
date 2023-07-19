/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/19 20:53:31 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "includes/cub3d.h"

void	draw_ray_minimap(t_root *game)
{
	//draw_any_line(game, (t_coord){game->player.x_pos, game->player.y_pos}, (t_coord){game->ray.rayDirX + 10, game->ray.rayDirY + 10}, 0x00FF0000, game->win2);
	put_img_to_img(&game->mini_background, game->mini_player, game->player.y_pos, game->player.x_pos); // inverted for minimap
	mlx_put_image_to_window(game->mlx, game->win2, game->mini_background.img, 0,0);
}

int	game_loop(t_root *game)
{
 	
	draw_back(game); // draw ceiling and floor
	dda_calculation(game);
	draw_sprite(game);
	//draw_ray_minimap(game);
	check_mouse_lock(game);
	player_animation(game);
	put_img_to_img(&game->background, game->bar, 0,668);
	put_img_to_img(&game->background, game->player, 448,539);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	move_player(game);
	return (0);
}

int	main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	t_root game;
	
	game.map_cols = 10;
	game.map_lines = 10;
	game.map = malloc(sizeof(char *) * 10);
	
	game.map[0] = ft_strdup("1111111111");
	game.map[1] = ft_strdup("1000010101");
	game.map[2] = ft_strdup("1001010101");
	game.map[3] = ft_strdup("1010010101");
	game.map[4] = ft_strdup("1100000111");
	game.map[5] = ft_strdup("1000001001");
	game.map[6] = ft_strdup("1001101001");
	game.map[7] = ft_strdup("1000001001");
	game.map[8] = ft_strdup("1000001101");
	game.map[9] = ft_strdup("1111111111");

	game.player.x_pos = 4.5;
	game.player.y_pos = 4.5;
	game.barrel.x_pos = 3.5;
	game.barrel.y_pos = 6.5;
	game.f_color = create_trgb(TRANSPARENCY, 128 ,128,128); // receive from parse in the future
	game.c_color = create_trgb(TRANSPARENCY, 0,0,0); // receive from parse in the future
	game.init_dir = 'W'; // receive from parse in the future
	
	init_values(&game);

	game.mlx = mlx_init();
	game.background.img = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	game.background.addr = mlx_get_data_addr(game.background.img, &game.background.bits_per_pixel, &game.background.line_length,
								&game.background.endian);
	game.mini_background.img = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	game.mini_background.addr = mlx_get_data_addr(game.mini_background.img, &game.mini_background.bits_per_pixel, &game.mini_background.line_length,
								&game.mini_background.endian);

	game.bar.img = mlx_xpm_file_to_image(game.mlx, "./assets/hbar.xpm", &game.bar.w, &game.bar.h);
	game.bar.addr = mlx_get_data_addr(game.bar.img, &game.bar.bits_per_pixel, &game.bar.line_length, &game.bar.endian);

	game.player.img = mlx_xpm_file_to_image(game.mlx, "./assets/gun.xpm", &game.player.w, &game.player.h);
	game.player.addr = mlx_get_data_addr(game.player.img, &game.player.bits_per_pixel, &game.player.line_length, &game.player.endian);
	
	game.barrel.img = mlx_xpm_file_to_image(game.mlx, "./assets/barrel.xpm", &game.barrel.w, &game.barrel.h);
	game.barrel.addr = mlx_get_data_addr(game.barrel.img, &game.barrel.bits_per_pixel, &game.barrel.line_length, &game.barrel.endian);
	
/* 	game.mini_player.img = mlx_xpm_file_to_image(game.mlx, "./assets/gun.xpm", &game.mini_player.w, &game.mini_player.h);
	game.mini_player.addr = mlx_get_data_addr(game.mini_player.img, &game.mini_player.bits_per_pixel, &game.mini_player.line_length, &game.mini_player.endian); */
	
	game.wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/tetris.xpm", &game.wall.w, &game.wall.h);
	game.wall.addr = mlx_get_data_addr(game.wall.img, &game.wall.bits_per_pixel, &game.wall.line_length, &game.wall.endian);

	
	game.wall1.img = mlx_xpm_file_to_image(game.mlx, "./assets/pacman.xpm", &game.wall1.w, &game.wall1.h);
	game.wall1.addr = mlx_get_data_addr(game.wall1.img, &game.wall1.bits_per_pixel, &game.wall1.line_length, &game.wall1.endian);

	game.wall2.img = mlx_xpm_file_to_image(game.mlx, "./assets/pong.xpm", &game.wall2.w, &game.wall2.h);
	game.wall2.addr = mlx_get_data_addr(game.wall2.img, &game.wall2.bits_per_pixel, &game.wall2.line_length, &game.wall2.endian);
	
	game.wall3.img = mlx_xpm_file_to_image(game.mlx, "./assets/asteroids.xpm", &game.wall3.w, &game.wall3.h);
	game.wall3.addr = mlx_get_data_addr(game.wall3.img, &game.wall3.bits_per_pixel, &game.wall3.line_length, &game.wall3.endian);
	
	game.win = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	//game.win2 = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "minimap");
	mlx_hook(game.win, 02, (1L<<0), input, &game);
	mlx_hook(game.win, 03, (1L<<1), input_release, &game);
	mlx_hook(game.win, 17, 1L<<0, exit_game_request, &game);
	mlx_hook(game.win, 04, (1L<<2), mouse_input, &game);
	mlx_hook(game.win, 05, (1L<<3), mouse_input_release, &game);
	mlx_hook(game.win, 06, (1L<<6), mouse_move, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
