/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:38:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/17 16:11:31 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <time.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx_int.h"

/* KEY MACROS */
# define ESC 65307
# define STRAFE_RIGHT 100
# define STRAFE_LEFT 97
# define UP 119
# define DOWN 115
# define TURN_RIGHT 65363
# define TURN_LEFT 65361
# define F1 65470

# define TRANSPARENCY 0x00980088

# define MARGIN 0.2f

# define TRUE 1
# define FALSE 0

typedef struct s_coord
{
	int x;
	int y;
}			t_coord;

typedef struct s_calc
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int mapY;
	int mapX;
}			t_calc;

typedef struct s_ray
{
	float	rayDirX;
	float	rayDirY;
	float	sideDistX;
	float	sideDistY;
	float	deltaDistX;
	float	deltaDistY;
	float	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit; //was there a wall hit?
	int		side; // what side of wall was hited;

}			t_ray;

typedef struct s_sprite {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		h;
	int		w;
	float	x_pos;
	float	y_pos;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	angle;
}			t_sprite;

typedef struct s_root {
	void		*mlx;
	void		*win;
	void		*win2;
	t_sprite	player;
	t_sprite	mini_background;
	t_sprite	wall;
	t_sprite	background;
	t_sprite	sky;
	char		**map;
	int			map_cols;
	int			map_lines;
	clock_t		time;
	clock_t		old_time;
	float		moveSpeed;
	float		rotSpeed;
	unsigned int buffer[600][800];
	t_ray		ray;
	t_calc		calc;
	int			keys[7];

	Cursor cursor;
	Pixmap blank;
	XColor dummy;
}			t_root;

// PROTOTYPE

/* SETUP INIT */
void	init_values(t_root *game);

/* EXIT */
int		exit_game_request(t_root *game);

/* MOVES */
void	turn_left(t_root *game);
void	turn_right(t_root *game);
void	move_forward(t_root *game);
void	move_backward(t_root *game);
void	strafe_right(t_root *game);
void	strafe_left(t_root *game);
void	move_player(t_root *game);
int		mouse_move(int x, int y, t_root *game);

/* DRAW UTIS*/
void	my_mlx_pixel_put(t_sprite *data, int x, int y, int color);
void	put_img_to_img(t_sprite *dst, t_sprite src, int x, int y);
void	put_draw_to_img(t_sprite *dst, t_sprite src, int x, int y);
int		get_pixel_img(t_sprite img, int x, int y);

/* DRAW */
void	draw_walls(t_root *game, int col);

/* MINIMAP */
void	draw_minimap(t_root *root, char **map);
void	draw_mini_player(t_root *root);

/* 2D MAP*/
void	draw_2dmap(t_root *root, char **map);

/* UI */
void	check_mouse_lock(t_root *game);

/* HOOK HANDLERS */
int	input_release(int keycode, t_root *root);
int	input(int keycode, t_root *root);
#endif