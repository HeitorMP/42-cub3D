/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/15 16:46:54 by hmaciel-         ###   ########.fr       */
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
	int w = 800;
	game->time = clock();
	draw_back(game);
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


		//******************** DESENHA APENAS NAS PAREDES *****************************8

		//calculate value of wallX
		//int texNum = game->map[mapX][mapY] - 1;
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = game->player.y_pos + perpWallDist * rayDirY;
		else
			wallX = game->player.x_pos + perpWallDist * rayDirX;
		wallX -= floor((wallX));
	
		//x coordinate on the texture
		int texX = (int)(wallX * (double)(64));
		if(side == 0 && rayDirX > 0) texX = 64 - texX - 1;
		if(side == 1 && rayDirY < 0) texX = 64 - texX - 1;

		
		
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * 64 / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - 600 / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (64 - 1);
			texPos += step;
			unsigned int color = get_pixel_img(game->wall, texX, texY);//texture[texNum][64 * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			//if(side == 1) color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&game->background, x, y, color);
		}

		/* int	color = 0;

		if (game->map[mapX][mapY] == '1')
			color = 0x00F80000;
		if (side == 1) {color = color / 2;}
		draw_line(game, drawStart, drawEnd, color, x); */
	}
	game->old_time = clock();
	put_img_to_img(&game->background, game->player, 380,480);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	game->frameTime = (float)(game->old_time - game->time) / CLOCKS_PER_SEC;
	float fps = CLOCKS_PER_SEC / (game->old_time - game->time);
	printf("%f\n", fps);
	return (0);
}

int	input(int keycode, t_root *root)
{
	double moveSpeed = root->frameTime * 15.0f; //the constant value is in squares/second
	double rotSpeed = root->frameTime * 13.0f; //the constant value is in radians/second
	(void)rotSpeed;
	if (keycode == ESC)
		exit_game_request(root);
	else if (keycode == UP || keycode == DOWN || \
			keycode == LEFT || keycode == RIGHT)
	{
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
		mlx_destroy_image(root->mlx, root->background.img);
		//mlx_destroy_image(root->mlx, root->player.img);
		root->background.img = mlx_new_image(root->mlx, 800, 600);
		//root->player.img = mlx_xpm_file_to_image(&root->player, "./assets/gun.xpm", &root->player.w, &root->player.h);
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
	//game.player.img = mlx_new_image(game.mlx, 128, 128);
	game.player.img = mlx_xpm_file_to_image(game.mlx, "./assets/gun.xpm", &game.player.w, &game.player.h);
	game.player.addr = mlx_get_data_addr(game.player.img, &game.player.bits_per_pixel, &game.player.line_length, &game.player.endian);
	
	game.wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/greystone.xpm", &game.wall.w, &game.wall.h);
	game.wall.addr = mlx_get_data_addr(game.wall.img, &game.wall.bits_per_pixel, &game.wall.line_length, &game.wall.endian);
	
	game.win = mlx_new_window(game.mlx, 800, 600, "cub3d");		
	mlx_hook(game.win, 17, 1L<<0, exit_game_request, &game);
	mlx_hook(game.win, 02, 0, input, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
