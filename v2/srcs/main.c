/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/16 18:16:16 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "includes/cub3d.h"

void	draw_back(t_root *root)
{
	int y = 0;
	int x = 0;
	while (y < 600)
	{
		while (x < 800)
		{
			if (y < 300)
				my_mlx_pixel_put(&root->background, x, y, 0x000000FF);
			else
				my_mlx_pixel_put(&root->background, x, y, 0x00808080);
			x++;
		}
		x = 0;
		y++;
	}

}

void	draw_line(t_root *root, int begin, int end, int color, int col)
{
/* 	if(end < begin)
		ft_swap(&begin, &end);
	 */
	while (begin < end)
	{
		my_mlx_pixel_put(&root->background, col, begin, color);
		begin++;
	}
}


int	exit_game_request(t_root *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	printf("Good bye and thanks for playing!!\n");
	exit (0);
	return (1);
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
		int side = 0; //was a NS or a EW wall hit? */
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

		//******************** DESENHA APENAS NAS PAREDES *****************************8
		draw_walls(game, x);
	}
	put_img_to_img(&game->background, game->player, 380,480);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	return (0);
}

int	input(int keycode, t_root *root)
{
	if (keycode == ESC)
		exit_game_request(root);
	else if (keycode == UP || keycode == DOWN || \
			keycode == STRAFE_LEFT || keycode == STRAFE_RIGHT || \
			keycode == TURN_RIGHT || keycode == TURN_LEFT)
	{
		if (keycode == UP)
			move_forward(root);
		if (keycode == STRAFE_RIGHT)
			strafe_right(root);
		if (keycode == DOWN)
			move_backward(root);
		if (keycode == STRAFE_LEFT)
			strafe_left(root);
		if (keycode == TURN_RIGHT)
			turn_right(root);
		if (keycode == TURN_LEFT)
			turn_left(root);

		mlx_destroy_image(root->mlx, root->background.img); // refresh main background image;
		root->background.img = mlx_new_image(root->mlx, 800, 600);
	}
	return (0);
}

int	mouse_move(int x, int y, t_root *game)
{
	float	oldDirX;
	float	oldPlaneX;
	static int	oldx;
	int			direction;

	(void)y;
	(void)x;
	direction = 2;
	
	printf("%d\n", x);

	if (oldx < 800 / 2)
		direction = 1;
	else if (oldx > 800 / 2)
		direction = 0;

	oldDirX = game->player.dir_x;
	if (direction == 1) {
		game->player.dir_x = game->player.dir_x * cos(game->rotSpeed) - game->player.dir_y * sin(game->rotSpeed);
		game->player.dir_y = oldDirX * sin(game->rotSpeed) + game->player.dir_y * cos(game->rotSpeed);
		oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(game->rotSpeed) - game->player.plane_y * sin(game->rotSpeed);
		game->player.plane_y = oldPlaneX * sin(game->rotSpeed) + game->player.plane_y * cos(game->rotSpeed);
		direction = 2;
	}
	else if (direction == 0)
	{
		game->player.dir_x = game->player.dir_x * cos(-game->rotSpeed) - game->player.dir_y * sin(-game->rotSpeed);
		game->player.dir_y = oldDirX * sin(-game->rotSpeed) + game->player.dir_y * cos(-game->rotSpeed);
		oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-game->rotSpeed) - game->player.plane_y * sin(-game->rotSpeed);
		game->player.plane_y = oldPlaneX * sin(-game->rotSpeed) + game->player.plane_y * cos(-game->rotSpeed);
		direction = 2;
	}
	oldx = x;
	if (y != 600 / 2)
		mlx_mouse_move(game->mlx, game->win, 400, 300);

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

	//float posX = 22, posY = 12;  //x and y start position
	game.player.x_pos = 5;
	game.player.y_pos = 4;
	
	//float dirX = -1, dirY = 0; //initial direction vector
	game.player.dir_x = -1;
	game.player.dir_y = 0.1;
	
	//float planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	game.player.plane_x = 0;
	game.player.plane_y = 0.66;

	game.ray.side = 0;
	game.ray.hit = 0;

	game.mlx = mlx_init();

	game.background.img = mlx_new_image(game.mlx, 800, 600);
	game.background.addr = mlx_get_data_addr(game.background.img, &game.background.bits_per_pixel, &game.background.line_length,
								&game.background.endian);
	//game.player.img = mlx_new_image(game.mlx, 128, 128);
	game.player.img = mlx_xpm_file_to_image(game.mlx, "./assets/gun.xpm", &game.player.w, &game.player.h);
	game.player.addr = mlx_get_data_addr(game.player.img, &game.player.bits_per_pixel, &game.player.line_length, &game.player.endian);
	
	game.wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/greystone.xpm", &game.wall.w, &game.wall.h);
	game.wall.addr = mlx_get_data_addr(game.wall.img, &game.wall.bits_per_pixel, &game.wall.line_length, &game.wall.endian);
	
	game.win = mlx_new_window(game.mlx, 800, 600, "cub3d");		
	mlx_hook(game.win, 17, 1L<<0, exit_game_request, &game);
	mlx_hook(game.win, 02, 0, input, &game);
	mlx_hook(game.win, 06, (1L << 6), mouse_move, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
