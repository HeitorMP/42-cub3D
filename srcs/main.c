#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_sprite *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_minimap_walls(t_root *root, int map[6][8])
{
	int i, j, x, y;
	i = j = x = y = 0;

	t_sprite	wall;
	t_sprite	back;

	wall.img = mlx_new_image(root->mlx, 200, 100);
	wall.addr = mlx_get_data_addr(wall.img, &wall.bits_per_pixel, &wall.line_length,
								&wall.endian);
	back.img = mlx_new_image(root->mlx, 200, 100);
	back.addr = mlx_get_data_addr(back.img, &back.bits_per_pixel, &back.line_length,
								&back.endian);
	while(i < 6)
	{
		while (j < 8)
		{
			x = 0;
			y = 0;
			if (map[i][j] == 1)
			{
				while(y < 20)
				{
					while (x < 20)
					{
						my_mlx_pixel_put(&wall, x, y, 0x000000FF);
						x++;
					}
					x = 0;
					y++;
				}
				mlx_put_image_to_window(root->mlx, root->win, wall.img, j * 20, i * 20);
			}
			else
			{
				while(y < 20)
				{
					while (x < 20)
					{
						my_mlx_pixel_put(&back, x, y, 0x00808080);
						x++;
					}
					x = 0;
					y++;
				}
				mlx_put_image_to_window(root->mlx, root->win, back.img, j * 20, i * 20);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_player(t_root *root)
{
	int	i = 0;
	int	j = 0;

	int	map[6][8] = {
		{1,1,1,1,1,1,1,1},
		{1,0,0,1,0,0,0,1},
		{1,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	
	t_sprite angle;

	angle.img = mlx_new_image(root->mlx, 5, 5);
	angle.addr = mlx_get_data_addr(angle.img, &angle.bits_per_pixel, &angle.line_length,
								&angle.endian);
	while(i < 5)
	{
		while (j < 5)
		{
			my_mlx_pixel_put(&angle, j, i, 0x00FF0000);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	while(i < 10)
	{
		while (j < 10)
		{
			my_mlx_pixel_put(&root->player, j, i, 0x00000000);
			j++;
		}
		j = 0;
		i++;
	}
	draw_minimap_walls(root, map);
	mlx_put_image_to_window(root->mlx, root->win, angle.img, root->player.x_pos + (root->player.delta_x * 2), root->player.y_pos + (root->player.delta_y * 2));
	mlx_put_image_to_window(root->mlx, root->win, root->player.img, root->player.x_pos, root->player.y_pos);
}

int	input(int keycode, t_root *root)
{
	if (keycode == ESC)
		exit_game_request(root);
	else if (keycode == UP || keycode == DOWN || \
			keycode == LEFT || keycode == RIGHT)
	{
		if (keycode == UP) {
			root->player.x_pos += root->player.delta_x;
			root->player.y_pos += root->player.delta_y;
			}
		if (keycode == DOWN) {
			root->player.x_pos -= root->player.delta_x;
			root->player.y_pos -= root->player.delta_y;
		}
		if (keycode == LEFT) {
			root->player.angle -= 0.1;
			if (root->player.angle < 0)
			{
				root->player.angle += 2 * PI;
			}
			root->player.delta_x = cos(root->player.angle) * 5;
			root->player.delta_y = sin(root->player.angle) * 5;
		}
		if (keycode == RIGHT) {
			root->player.angle += 0.1;
			if (root->player.angle > 2 * PI)
			{
				root->player.angle -= 2 * PI;
			}
			root->player.delta_x = cos(root->player.angle) * 5;
			root->player.delta_y = sin(root->player.angle) * 5;
		}
	}
	draw_player(root);
	return (0);
}

int	main()
{
	t_root	root;

 	int	map[6][8] = {
		{1,1,1,1,1,1,1,1},
		{1,0,0,1,0,0,0,1},
		{1,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};

	root.player.y_pos = 0;
	root.player.x_pos = 0;
	root.player.delta_x = 0;
	root.player.delta_y = 0;
	root.player.angle = 0;

	root.mlx = mlx_init();
	root.win = mlx_new_window(root.mlx, 800, 600, "Cub3d");
	root.mini_background.img = mlx_new_image(root.mlx, 800, 600);
	root.mini_background.addr = mlx_get_data_addr(root.mini_background.img, &root.mini_background.bits_per_pixel, &root.mini_background.line_length,
								&root.mini_background.endian);

	root.player.img = mlx_new_image(root.mlx, 10, 10);
	root.player.addr = mlx_get_data_addr(root.player.img, &root.player.bits_per_pixel, &root.player.line_length,
								&root.player.endian);
	draw_minimap_walls(&root, map);
	mlx_hook(root.win, 02, 0, input, &root);
	//mlx_key_hook(root.win, input, &root);
	mlx_hook(root.win, 17, 1L<<0, exit_game_request, &root);
	mlx_loop(root.mlx);
	printf("teste\n");
	return (0);
}