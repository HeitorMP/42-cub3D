/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/18 08:59:20 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_back(t_root *game)
{
	int y = 0;
	int x = 0;
	while (y < 600)
	{
		while (x < 800)
		{
			if (y < 300)
				my_mlx_pixel_put(&game->background, x, y, game->c_color);
			else
				my_mlx_pixel_put(&game->background, x, y, game->f_color);
			x++;
		}
		x = 0;
		y++;
	}

}

void	draw_line(t_root *root, int begin, int end, int color, int col)
{
	while (begin < end)
	{
		my_mlx_pixel_put(&root->background, col, begin, color);
		begin++;
	}
}

void	draw_any_line(t_root *root, t_coord begin, t_coord end, int color, void *win)
{
	t_sprite	temp;
	t_coord	new_begin;
	int		pixel;
	double deltaX;
	double deltaY;

	if (begin.x == end.x && begin.y == end.y)
		return ;
	new_begin = begin;
	if (end.x < begin.x)
	{
		new_begin = end;
		end = begin;
	}
	printf("begin: %d - %d | end: %d - %d\n", new_begin.x, new_begin.y, end.x, end.y);
	deltaX = end.x - new_begin.x;
	deltaY = end.y - new_begin.y;
	temp.img = mlx_new_image(root->mlx, 64, 64);
	temp.addr = mlx_get_data_addr(temp.img, &temp.bits_per_pixel, &temp.line_length,
								&temp.endian);
	pixel = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixel;
	deltaY /= pixel;

	double pixelX = new_begin.x;
	double pixelY = new_begin.y;
	while (pixel)
	{
		my_mlx_pixel_put(&temp, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixel;
	}
	put_draw_to_img(&root->mini_background, temp, 0, 0);
	mlx_put_image_to_window(root->mlx, win, root->mini_background.img, new_begin.x, new_begin.y);
}

void	draw_ray_minimap(t_root *game)
{
	//draw_any_line(game, (t_coord){game->player.x_pos, game->player.y_pos}, (t_coord){game->ray.rayDirX + 10, game->ray.rayDirY + 10}, 0x00FF0000, game->win2);
	put_img_to_img(&game->mini_background, game->mini_player, game->player.y_pos, game->player.x_pos); // inverted for minimap
	mlx_put_image_to_window(game->mlx, game->win2, game->mini_background.img, 0,0);
}


int	game_loop(t_root *game)
{
	int w = 800; // in the future will be the size of window
	draw_back(game); // draw ceiling and floor
	for(int x = 0; x < w; x++) // x = size of columns in windows
	{
		//calculate ray position and direction
		float cameraX = 2 * x / (float)(w) - 1; //x-coordinate in camera space // -1 to correct view
		game->ray.rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
		game->ray.rayDirY = game->player.dir_y + game->player.plane_y * cameraX;

		//which box of the map we're in
		int mapX = (int)(game->player.x_pos);
		int mapY = (int)(game->player.y_pos);

		//length of ray from current position to next x or y-side
	/* 	float sideDistX;
		float sideDistY; */

		//length of ray from one x or y-side to next x or y-side
		//float deltaDistX;
		if (game->ray.rayDirX == 0)
		{
			game->ray.deltaDistX = 1e30;
		}
		else
		{
			game->ray.deltaDistX = fabs(1 / game->ray.rayDirX);
		}
		game->ray.deltaDistY = (game->ray.rayDirY == 0) ? 1e30 : fabs(1 / game->ray.rayDirY);

		//what direction to step in x or y-direction (either +1 or -1)
/* 		int stepX;
		int stepY; */

/* 		int hit = 0; //was there a wall hit?
		side = 0; //was a NS or a EW wall hit? */
		game->ray.hit = 0;
		if (game->ray.rayDirX < 0)
		{
			game->ray.stepX = -1;
			game->ray.sideDistX = (game->player.x_pos - mapX) * game->ray.deltaDistX;
		}
		else
		{
			game->ray.stepX = 1;
			game->ray.sideDistX = (mapX + 1.0 - game->player.x_pos) * game->ray.deltaDistX;
		}
		if (game->ray.rayDirY < 0)
		{
			game->ray.stepY = -1;
			game->ray.sideDistY = (game->player.y_pos - mapY) * game->ray.deltaDistY;
		}
		else
		{
			game->ray.stepY = 1;
			game->ray.sideDistY = (mapY + 1.0 - game->player.y_pos) * game->ray.deltaDistY;
		}

		while (game->ray.hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (game->ray.sideDistX < game->ray.sideDistY)
			{
				game->ray.sideDistX += game->ray.deltaDistX;
				mapX += game->ray.stepX;
				game->ray.side = 0;
			}
			else
			{
				game->ray.sideDistY += game->ray.deltaDistY;
				mapY += game->ray.stepY;
				game->ray.side = 1;
			}
			//Check if ray has hit a wall
			if (game->map[mapX][mapY] != '0')
				game->ray.hit = 1;
		}
		if(game->ray.side == 0)
			game->ray.perpWallDist = (game->ray.sideDistX - game->ray.deltaDistX);
		else
			game->ray.perpWallDist = (game->ray.sideDistY - game->ray.deltaDistY);

		game->calc.lineHeight = (int)(600 / game->ray.perpWallDist);
		game->calc.drawStart = (game->calc.lineHeight * -1) / 2 + 600 / 2;
		if(game->calc.drawStart < 0)
			game->calc.drawStart = 0;
		game->calc.drawEnd = game->calc.lineHeight / 2 + 600 / 2;
		if(game->calc.drawEnd >= 600)
			game->calc.drawEnd = 600 - 1;

		//******************** DESENHA APENAS NAS PAREDES *****************************
		draw_walls(game, x);
		//printf("%f\n", game->player.dir_y);
	}
	move_player(game);
	draw_ray_minimap(game);
	check_mouse_lock(game);
	put_img_to_img(&game->background, game->player, 300,480);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
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

	game.moveSpeed = 0.08f;
	game.rotSpeed = 0.03f;
	
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
	game.f_color = create_trgb(TRANSPARENCY, 128 ,128,128);
	game.c_color = create_trgb(TRANSPARENCY, 0,0,0);
	char dir = 'W';
	if (dir == 'E')
	{
		game.player.dir_x = 0.0f;
		game.player.dir_y = 1.0f;
		game.player.plane_x = 0.66;
		game.player.plane_y = 0;
	}
	else if (dir == 'W')
	{
		game.player.dir_x = 0.0f;
		game.player.dir_y = -1.0f;
		game.player.plane_x = -0.66;
		game.player.plane_y = 0;
	}

	else if (dir == 'S')
	{
		game.player.dir_x = 1.0f;
		game.player.dir_y = 0.1f;
		game.player.plane_x = 0;
		game.player.plane_y = -0.66;
	}
	else if (dir == 'N')
	{
		game.player.dir_x = -1.0f;
		game.player.dir_y = 0.0f;
		game.player.plane_x = 0;
		game.player.plane_y = 0.66;
	}

	game.ray.side = 0;
	game.ray.hit = 0;

	init_values(&game);
	game.mlx = mlx_init();

	game.background.img = mlx_new_image(game.mlx, 800, 600);
	game.background.addr = mlx_get_data_addr(game.background.img, &game.background.bits_per_pixel, &game.background.line_length,
								&game.background.endian);
	game.mini_background.img = mlx_new_image(game.mlx, 800, 600);
	game.mini_background.addr = mlx_get_data_addr(game.mini_background.img, &game.mini_background.bits_per_pixel, &game.mini_background.line_length,
								&game.mini_background.endian);
								
	game.player.img = mlx_xpm_file_to_image(game.mlx, "./assets/gun.xpm", &game.player.w, &game.player.h);
	game.player.addr = mlx_get_data_addr(game.player.img, &game.player.bits_per_pixel, &game.player.line_length, &game.player.endian);
	
	game.mini_player.img = mlx_xpm_file_to_image(game.mlx, "./assets/gun.xpm", &game.mini_player.w, &game.mini_player.h);
	game.mini_player.addr = mlx_get_data_addr(game.mini_player.img, &game.mini_player.bits_per_pixel, &game.mini_player.line_length, &game.mini_player.endian);
	
	game.wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/N1.xpm", &game.wall.w, &game.wall.h);
	game.wall.addr = mlx_get_data_addr(game.wall.img, &game.wall.bits_per_pixel, &game.wall.line_length, &game.wall.endian);
	
	game.wall1.img = mlx_xpm_file_to_image(game.mlx, "./assets/S1.xpm", &game.wall1.w, &game.wall1.h);
	game.wall1.addr = mlx_get_data_addr(game.wall1.img, &game.wall1.bits_per_pixel, &game.wall1.line_length, &game.wall1.endian);

	game.wall2.img = mlx_xpm_file_to_image(game.mlx, "./assets/E1.xpm", &game.wall2.w, &game.wall2.h);
	game.wall2.addr = mlx_get_data_addr(game.wall2.img, &game.wall2.bits_per_pixel, &game.wall2.line_length, &game.wall2.endian);
	
	game.wall3.img = mlx_xpm_file_to_image(game.mlx, "./assets/W1.xpm", &game.wall3.w, &game.wall3.h);
	game.wall3.addr = mlx_get_data_addr(game.wall3.img, &game.wall3.bits_per_pixel, &game.wall3.line_length, &game.wall3.endian);
	
	game.win = mlx_new_window(game.mlx, 800, 600, "cub3d");
	game.win2 = mlx_new_window(game.mlx, 800, 600, "minimap");
	mlx_hook(game.win, 17, 1L<<0, exit_game_request, &game);
	mlx_hook(game.win, 02, (1L<<0), input, &game);
	mlx_hook(game.win, 03, (1L<<1), input_release, &game);
	mlx_hook(game.win, 06, (1L << 6), mouse_move, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
