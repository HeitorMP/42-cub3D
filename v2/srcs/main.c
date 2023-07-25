/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/25 21:37:12 by hmaciel-         ###   ########.fr       */
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
/* 	printf("%f - %f\n", game.player.x_pos, game.player.y_pos);
	printf("file ea %s\n", file.ea);
	printf("file no %s\n", file.no);
	printf("file so %s\n", file.so);
	printf("file we %s\n", file.we);
	printf("num floor red %d\n", file.floor.red);
	printf("num floor green %d\n", file.floor.green);
	printf("num floor blue %d\n", file.floor.blue);
	printf("num ceiling red %d\n", file.ceilling.red);
	printf("num ceiling green %d\n", file.ceilling.green);
	printf("num ceiling blue %d\n", file.ceilling.blue); */
	
	game.map_cols = 33;
	game.map_lines = 14;
	game.map = malloc(sizeof(char *) * game.map_lines);
	
	game.map[0] = ft_strdup("1111111111111111111111111");
	game.map[1] = ft_strdup("1000000000110000000000001");
	game.map[2] = ft_strdup("1011000001110000000000001");
	game.map[3] = ft_strdup("1001000000000000000000001");
	game.map[4] = ft_strdup("1111111110110000011100001");
	game.map[5] = ft_strdup("100000000011000001110111111111111");
	game.map[6] = ft_strdup("11110111111111011100000010001");
	game.map[7] = ft_strdup("11110111111111011101010010001");
	game.map[8] = ft_strdup("11000000110101011100000010001");
	game.map[9] = ft_strdup("10000000000000001100000010001");
	game.map[10] = ft_strdup("10000000000000001101010010001");
	game.map[11] = ft_strdup("1100000111010101111101111000111");
	game.map[12] = ft_strdup("11110111 1110101 101111010001");
	game.map[13] = ft_strdup("11111111 1111111 111111111111");

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
