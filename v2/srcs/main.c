/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/23 16:48:44 by hmaciel-         ###   ########.fr       */
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
	game.map[6] = ft_strdup("100110D001");
	game.map[7] = ft_strdup("1000001001");
	game.map[8] = ft_strdup("1000001101");
	game.map[9] = ft_strdup("1111111111");

	game.player.x_pos = 2.5;
	game.player.y_pos = 4.5;

	game.f_color = create_trgb(TRANSPARENCY, 128 ,128,128); // receive from parse in the future
	game.c_color = create_trgb(TRANSPARENCY, 0,0,0); // receive from parse in the future
	game.init_dir = 'N'; // receive from parse in the future
	
	init_values(&game);

	game.mlx = mlx_init();
	game.background.img = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	game.background.addr = mlx_get_data_addr(game.background.img, &game.background.bits_per_pixel, &game.background.line_length,
								&game.background.endian);

	game.north_wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/N1.xpm", &game.north_wall.w, &game.north_wall.h);
	game.north_wall.addr = mlx_get_data_addr(game.north_wall.img, &game.north_wall.bits_per_pixel, &game.north_wall.line_length, &game.north_wall.endian);
	
	game.south_wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/S1.xpm", &game.south_wall.w, &game.south_wall.h);
	game.south_wall.addr = mlx_get_data_addr(game.south_wall.img, &game.south_wall.bits_per_pixel, &game.south_wall.line_length, &game.south_wall.endian);

	game.east_wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/E1.xpm", &game.east_wall.w, &game.east_wall.h);
	game.east_wall.addr = mlx_get_data_addr(game.east_wall.img, &game.east_wall.bits_per_pixel, &game.east_wall.line_length, &game.east_wall.endian);
	
	game.west_wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/W1.xpm", &game.west_wall.w, &game.west_wall.h);
	game.west_wall.addr = mlx_get_data_addr(game.west_wall.img, &game.west_wall.bits_per_pixel, &game.west_wall.line_length, &game.west_wall.endian);

	
	game.win = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	mlx_hook(game.win, 02, (1L<<0), input, &game);
	mlx_hook(game.win, 03, (1L<<1), input_release, &game);
	mlx_hook(game.win, 17, 1L<<0, exit_game_request, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
