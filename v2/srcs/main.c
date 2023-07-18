/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/18 17:48:19 by hmaciel-         ###   ########.fr       */
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
	while (y < SCREENHEIGHT)
	{
		while (x < SCREENWIDTH)
		{
			if (y < SCREENHEIGHT / 2)
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
	temp.img = mlx_new_image(root->mlx, IMGSIZE, IMGSIZE);
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

void	player_animation(t_root *game)
{
	static int count_anim;

	if (count_anim >= 60)
		count_anim = 0;

	count_anim++;
	mlx_destroy_image(game->mlx, game->player.img);
	if (count_anim < 20)
	{
		game->player.img = mlx_xpm_file_to_image(game->mlx, "./assets/gun.xpm", &game->player.w, &game->player.h);
		game->player.addr = mlx_get_data_addr(game->player.img, &game->player.bits_per_pixel, &game->player.line_length, &game->player.endian);
	}
	else if (count_anim < 40)
	{
		game->player.img = mlx_xpm_file_to_image(game->mlx, "./assets/gun2.xpm", &game->player.w, &game->player.h);
		game->player.addr = mlx_get_data_addr(game->player.img, &game->player.bits_per_pixel, &game->player.line_length, &game->player.endian);
	}
	else
	{
		game->player.img = mlx_xpm_file_to_image(game->mlx, "./assets/gun3.xpm", &game->player.w, &game->player.h);
		game->player.addr = mlx_get_data_addr(game->player.img, &game->player.bits_per_pixel, &game->player.line_length, &game->player.endian);
	}
	
}

int	game_loop(t_root *game)
{
	draw_back(game); // draw ceiling and floor
	for(int x = 0; x < SCREENWIDTH; x++) // x = size of columns in windows
	{
		//calculate ray position and direction
		float cameraX = 2 * x / (float)(SCREENWIDTH) - 1; //x-coordinate in camera space // -1 to correct view
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

		game->calc.lineHeight = (int)(SCREENHEIGHT / game->ray.perpWallDist);
		game->calc.drawStart = (game->calc.lineHeight * -1) / 2 + SCREENHEIGHT / 2;
		if(game->calc.drawStart < 0)
			game->calc.drawStart = 0;
		game->calc.drawEnd = game->calc.lineHeight / 2 + SCREENHEIGHT / 2;
		if(game->calc.drawEnd >= SCREENHEIGHT)
			game->calc.drawEnd = SCREENHEIGHT - 1;

		//******************** DESENHA APENAS NAS PAREDES *****************************
		draw_walls(game, x);
		//printf("%f\n", game->player.dir_y);
		game->barrel.ZBuffer[x] = game->ray.perpWallDist;
	}
	/* Draw sprite */
	game->barrel.sprite_distance = ((game->player.x_pos - game->barrel.x_pos) * (game->player.x_pos - game->barrel.x_pos) + (game->player.y_pos - game->barrel.y_pos) * (game->player.y_pos - game->barrel.y_pos));
	double spriteX = game->barrel.x_pos - game->player.x_pos;
	double spriteY = game->barrel.y_pos - game->player.y_pos;
	double invDet = 1.0 / (game->player.plane_x *  game->player.dir_y - game->player.dir_x * game->player.plane_y); //required for correct matrix multiplication

	double transformX = invDet * (game->player.dir_y * spriteX - game->player.dir_x * spriteY);
	double transformY = invDet * (-game->player.plane_y * spriteX + game->player.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
	int spriteScreenX = (int)((SCREENWIDTH / 2) * (1 + transformX / transformY));

	 //calculate height of the sprite on screen
      int spriteHeight = abs((int)(SCREENHEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + SCREENHEIGHT / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + SCREENHEIGHT / 2;
      if(drawEndY >= SCREENHEIGHT) drawEndY = SCREENHEIGHT - 1;

	   //calculate width of the sprite
      int spriteWidth = abs( (int)(SCREENHEIGHT / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= SCREENWIDTH) drawEndX = SCREENWIDTH - 1;

	  for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * IMGSIZE / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < SCREENWIDTH && transformY < game->barrel.ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - SCREENHEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * IMGSIZE) / spriteHeight) / 256;
		  my_mlx_pixel_put(&game->background, stripe, y, get_pixel_img(game->barrel, texX, texY));
          //unsigned color = texture[sprite[spriteOrder[i]].texture][IMGSIZE * texY + texX]; //get current color from the texture
          //if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
	  }
	move_player(game);
	//draw_ray_minimap(game);
	check_mouse_lock(game);
	player_animation(game);
	put_img_to_img(&game->background, game->player, 440,500);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	put_img_to_img(&game->background, game->bar, 0,628);
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
	
	game.mini_player.img = mlx_xpm_file_to_image(game.mlx, "./assets/gun.xpm", &game.mini_player.w, &game.mini_player.h);
	game.mini_player.addr = mlx_get_data_addr(game.mini_player.img, &game.mini_player.bits_per_pixel, &game.mini_player.line_length, &game.mini_player.endian);
	
	game.wall.img = mlx_xpm_file_to_image(game.mlx, "./assets/N.xpm", &game.wall.w, &game.wall.h);
	game.wall.addr = mlx_get_data_addr(game.wall.img, &game.wall.bits_per_pixel, &game.wall.line_length, &game.wall.endian);

	
	game.wall1.img = mlx_xpm_file_to_image(game.mlx, "./assets/S.xpm", &game.wall1.w, &game.wall1.h);
	game.wall1.addr = mlx_get_data_addr(game.wall1.img, &game.wall1.bits_per_pixel, &game.wall1.line_length, &game.wall1.endian);

	game.wall2.img = mlx_xpm_file_to_image(game.mlx, "./assets/E.xpm", &game.wall2.w, &game.wall2.h);
	game.wall2.addr = mlx_get_data_addr(game.wall2.img, &game.wall2.bits_per_pixel, &game.wall2.line_length, &game.wall2.endian);
	
	game.wall3.img = mlx_xpm_file_to_image(game.mlx, "./assets/W.xpm", &game.wall3.w, &game.wall3.h);
	game.wall3.addr = mlx_get_data_addr(game.wall3.img, &game.wall3.bits_per_pixel, &game.wall3.line_length, &game.wall3.endian);
	
	game.win = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	//game.win2 = mlx_new_window(game.mlx, SCREENWIDTH, SCREENHEIGHT, "minimap");
	mlx_hook(game.win, 17, 1L<<0, exit_game_request, &game);
	mlx_hook(game.win, 02, (1L<<0), input, &game);
	mlx_hook(game.win, 03, (1L<<1), input_release, &game);
	mlx_hook(game.win, 06, (1L << 6), mouse_move, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
