#include "../includes/cub3d.h"

#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 // one degree in radians

void	draw_line(t_root *root, t_coord begin, t_coord end, int color, void *win)
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
	temp.img = mlx_new_image(root->mlx, 800, 600);
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
	//draw_2dmap(root, root->map);
	put_draw_to_img(&root->background, temp, 0,0);
	mlx_destroy_image(root->mlx, temp.img);
	mlx_put_image_to_window(root->mlx, win, root->background.img, 0, 0);
}

float	dist(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return (sqrt((bx-ax) * (bx - ax) + (by-ay) * (by-ay)));
}


void	draw_ray(t_root *root)
{
	int r, mx, my, dof, hx, hy, vx, vy, finalD;
	float aTan, nTan, rx, ry, ra, xo, yo;

	xo = 0;
	yo = 0;
	ry = 0;
	rx = 0;
	vy = 0;
	vx = 0;
	hx = 0;
	hy = 0;
	finalD = 0;
	ra = root->player.angle - DR * 30;
	if (ra<0)
		ra+=2*PI;
	if (ra > 2*PI)
		ra-=2*PI;
	float disH, disV;
	for (r = 0; r<60; r++)
	{
		/* HORIZONTAL CHECKER */
		dof = 0;
		disH=100000; hx = root->player.x_pos; hy = root->player.y_pos;
		aTan=-1/tan(ra);
		if (ra>PI) { ry=(((int)root->player.y_pos>>6)<<6)-0.0001; rx = (root->player.y_pos-ry)*aTan+root->player.x_pos; yo=-64; xo=-yo*aTan;}
		if (ra<PI) { ry=(((int)root->player.y_pos>>6)<<6)+64; rx = (root->player.y_pos-ry)*aTan+root->player.x_pos; yo=64; xo=-yo*aTan;}
		if (ra == 0 || ra == PI) {rx=root->player.x_pos; ry=root->player.y_pos; dof=5;}
		while(dof<5)
		{
			mx=(int)(rx)>>6;
			my=(int)(ry)>>6;
			printf("ra = %f - my = %d - mx = %d\n", ra, my, mx);
			if((mx >= 0 && my >= 0) && (mx < 5 && my < 5) && root->map[my][mx] == '1')
			{
				hx = rx; hy = ry; disH = dist(root->player.x_pos,root->player.y_pos,hx, hy, ra);
				dof = 5;

			}//hit wall
			else {rx+=xo; ry+=yo; dof += 1;}
		}

		/* VERTICAL CHECKER */
		dof = 0;
		disV=100000; vx = root->player.x_pos; vy = root->player.y_pos;
		nTan=-tan(ra);
		if (ra > P2 && ra < P3) { rx=(((int)root->player.x_pos>>6)<<6)-0.0001; ry = (root->player.x_pos-rx)*nTan+root->player.y_pos; xo=-64; yo=-xo*nTan;}
		if (ra < P2 || ra > P3) { rx=(((int)root->player.x_pos>>6)<<6)+64; ry = (root->player.x_pos-rx)*nTan+root->player.y_pos; xo=64; yo=-xo*nTan;}
		if (ra==0 || ra == PI) {rx=root->player.x_pos; ry=root->player.y_pos; dof=5;}
		while(dof<5)
		{
			mx=rx/64;
			my=ry/64;
			printf("ra = %f - my = %d - mx = %d\n", ra, my, mx);
			if((mx >= 0 && my >= 0) && (mx < 5 && my < 5) && root->map[my][mx] == '1')
			{
				vx = rx; vy = ry; disV = dist(root->player.x_pos,root->player.y_pos,vx, vy, ra);
				dof = 5;
			}
			else {rx+=xo; ry+=yo; dof += 1;}
		}
		if (disV<disH) {rx=vx; ry=vy; finalD=disV;}
		if (disH<disV) {rx=hx; ry=hy; finalD=disH;}
		//draw_line(root, (t_coord){root->player.x_pos, root->player.y_pos}, (t_coord){rx, ry}, 0x00FF0000);
		float lineH=(64*320)/finalD; if (lineH>320) {lineH=320;}
		//float lineO=160-lineH/2;
		draw_line(root, (t_coord){r*5+200,0}, (t_coord){r*5+200,lineH}, 0x00FF0000, root->win);
		/* Draw 3d*/

		ra+=DR;
		if (ra<0)
			ra+=2*PI;
		if (ra > 2*PI)
			ra-=2*PI;
	}
	mlx_destroy_image(root->mlx, root->background.img);
	root->background.img = mlx_new_image(root->mlx, 800, 600);
}

int	input(int keycode, t_root *root)
{
	if (keycode == ESC)
		exit_game_request(root);
	else if (keycode == UP || keycode == DOWN || \
			keycode == LEFT || keycode == RIGHT)
	{
		if (keycode == UP)
			move_forward(root);
		if (keycode == DOWN)
			move_backward(root);
		if (keycode == LEFT)
			turn_left(root);
		if (keycode == RIGHT)
			turn_right(root);
	}
	return (0);
}

int	game_loop(t_root *root)
{
	draw_mini_player(root);
	draw_ray(root);
	mlx_do_sync(root->mlx);
	return (0);
}

int	main()
{
	t_root	root;

	root.map = ft_calloc(sizeof(char *), 6);
	for (int i = 0; i < 5; i++)
		root.map[i] = ft_calloc(sizeof(char), 6);
	root.map[0] = ft_strdup("11111");
	root.map[1] = ft_strdup("10101");
	root.map[2] = ft_strdup("10101");
	root.map[3] = ft_strdup("10001");
	root.map[4] = ft_strdup("11111");

	root.player.y_pos = 64;
	root.player.x_pos = 64;
	root.player.delta_x = 0;
	root.player.delta_y = 0;
	root.player.angle = 0;

	root.mlx = mlx_init();
	root.win = mlx_new_window(root.mlx, 800, 600, "Cub3d");
	root.win2 = mlx_new_window(root.mlx, 800, 600, "2dmap");

	root.mini_background.img = mlx_new_image(root.mlx, 800, 600);
	root.mini_background.addr = mlx_get_data_addr(root.mini_background.img, &root.mini_background.bits_per_pixel, &root.mini_background.line_length,
								&root.mini_background.endian);
	
	root.background.img = mlx_new_image(root.mlx, 800, 600);
	root.background.addr = mlx_get_data_addr(root.background.img, &root.background.bits_per_pixel, &root.background.line_length,
								&root.background.endian);
	mlx_put_image_to_window(root.mlx, root.win2, root.mini_background.img, 0, 0);

	root.player.img = mlx_new_image(root.mlx, 10, 10);
	root.player.addr = mlx_get_data_addr(root.player.img, &root.player.bits_per_pixel, &root.player.line_length,
								&root.player.endian);

	draw_2dmap(&root, root.map);
	
	mlx_hook(root.win, 02, 0, input, &root);
	mlx_loop_hook(root.mlx, game_loop, &root);
	mlx_hook(root.win, 17, 1L<<0, exit_game_request, &root);
	mlx_loop(root.mlx);
	return (0);
}