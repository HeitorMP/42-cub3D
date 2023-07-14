/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 202'3'/07/14 10:51:41 by hmaciel-          #+#    #+#             */
/*   Updated: 202'3'/07/14 11:5'3':51 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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
	int w = 800;
	game->time = clock();
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		float cameraX = 2 * x / (float)(w) - 1; //x-coordinate in camera space
		float rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
		float rayDirY = game->player.dir_y + game->player.plane_y * cameraX;

		//which box of the map we're in
		int mapX = (int)(game->player.x_pos);
		int mapY = (int)(game->player.y_pos);

		//length of ray from current position to next x or y-side
		float sideDistX;
		float sideDistY;

		//length of ray from one x or y-side to next x or y-side
		float deltaDistX;
		if (rayDirX == 0)
		{
			deltaDistX = 1e30;
		}
		else
		{
			deltaDistX = fabs(1 / rayDirX);
		}
		float deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		float perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side = 0; //was a NS or a EW wall hit?


		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.x_pos - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.x_pos) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y_pos - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.y_pos) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (game->map[mapX][mapY] != '0')
				hit = 1;
		}
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(600 / perpWallDist);
		int drawStart = (lineHeight * -1) / 2 + 600 / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + 600 / 2;
		if(drawEnd >= 600)
			drawEnd = 600 - 1;

		int	color = 0;

		if (game->map[mapX][mapY] == '1')
			color = 0x000000FF;
		if (side == 1) {color = color / 2;}
		draw_line(game, drawStart, drawEnd, color, x);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	game->old_time = clock();
	game->frameTime = (float)(game->old_time - game->time) / CLOCKS_PER_SEC;
	//ft_printf("%f\n", game->frameTime);
	return (0);
}

int	input(int keycode, t_root *root)
{
	double moveSpeed = root->frameTime * 10.0f; //the constant value is in squares/second
	double rotSpeed = root->frameTime * 5.0f; //the constant value is in radians/second
	(void)rotSpeed;
	if (keycode == ESC)
		exit_game_request(root);
	else if (keycode == UP || keycode == DOWN || \
			keycode == LEFT || keycode == RIGHT)
	{
		ft_printf("%d - %d\n", root->player.y_pos, root->player.x_pos);
		mlx_clear_window(root->mlx, root->win);
		mlx_destroy_image(root->mlx, root->background.img);
		root->background.img = mlx_new_image(root->mlx, 800, 600);
	
		if (keycode == UP) {
			if(root->map[(int)(root->player.x_pos + root->player.dir_x * moveSpeed)][(int)root->player.y_pos] == '0')
				root->player.x_pos += root->player.dir_x * moveSpeed;
			if(root->map[(int)(root->player.x_pos)][(int)(root->player.y_pos + root->player.dir_y * moveSpeed)] == '0')
				root->player.y_pos += root->player.dir_y * moveSpeed;
		}
		//move_forward(root);
		if (keycode == DOWN)
		{
			if(root->map[(int)(root->player.x_pos - root->player.dir_x * moveSpeed)][(int)root->player.y_pos] == '0')
				root->player.x_pos -= root->player.dir_x * moveSpeed;
			if(root->map[(int)(root->player.x_pos)][(int)(root->player.y_pos - root->player.dir_y * moveSpeed)] == '0')
				root->player.y_pos -= root->player.dir_y * moveSpeed;
		}
			//move_backward(root);
		if (keycode == RIGHT)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = root->player.dir_x;
			root->player.dir_x = root->player.dir_x * cos(-rotSpeed) - root->player.dir_y * sin(-rotSpeed);
			root->player.dir_y = oldDirX * sin(-rotSpeed) + root->player.dir_y * cos(-rotSpeed);
			double oldPlaneX = root->player.plane_x;
			root->player.plane_x = root->player.plane_x * cos(-rotSpeed) - root->player.plane_y * sin(-rotSpeed);
			root->player.plane_y = oldPlaneX * sin(-rotSpeed) + root->player.plane_y * cos(-rotSpeed);
		}
			//turn_left(root);
		if (keycode == LEFT)
		{
			 //both camera direction and camera plane must be rotated
			double oldDirX = root->player.dir_x;
			root->player.dir_x = root->player.dir_x * cos(rotSpeed) - root->player.dir_y * sin(rotSpeed);
			root->player.dir_y = oldDirX * sin(rotSpeed) + root->player.dir_y * cos(rotSpeed);
			double oldPlaneX = root->player.plane_x;
			root->player.plane_x = root->player.plane_x * cos(rotSpeed) - root->player.plane_y * sin(rotSpeed);
			root->player.plane_y = oldPlaneX * sin(rotSpeed) + root->player.plane_y * cos(rotSpeed);
		}
			//turn_right(root);
	}
	return (0);
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	t_root game;
	game.map_cols = 10;
	game.map_lines = 10;
	game.map = malloc(sizeof(char *) * 10);
	
	game.map[0] = ft_strdup("1111111111");
	game.map[1] = ft_strdup("1000000001");
	game.map[2] = ft_strdup("1001000001");
	game.map[3] = ft_strdup("1010000001");
	game.map[4] = ft_strdup("1100001111");
	game.map[5] = ft_strdup("1000001001");
	game.map[6] = ft_strdup("1001101001");
	game.map[7] = ft_strdup("1000001001");
	game.map[8] = ft_strdup("1000001101");
	game.map[9] = ft_strdup("1111111111");

	//float posX = 22, posY = 12;  //x and y start position
	game.player.x_pos = 5;
	game.player.y_pos = 5;
	
	//float dirX = -1, dirY = 0; //initial direction vector
	game.player.dir_x = -1;
	game.player.dir_y = 0;
	
	//float planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	game.player.plane_x = 0;
	game.player.plane_y = 0.66;

	game.mlx = mlx_init();

	game.background.img = mlx_new_image(game.mlx, 800, 600);
	game.background.addr = mlx_get_data_addr(game.background.img, &game.background.bits_per_pixel, &game.background.line_length,
								&game.background.endian);
	game.win = mlx_new_window(game.mlx, 800, 600, "cub3d");
	mlx_hook(game.win, 17, 1L<<0, exit_game_request, &game);
	mlx_hook(game.win, 02, 0, input, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
