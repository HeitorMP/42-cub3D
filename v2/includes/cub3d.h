/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:38:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/22 17:12:23 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include "key_macros.h"
# include "consts.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/includes/libft.h"

typedef struct s_calc_wall
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		map_y;
	int		map_x;
	float	wallx;
	int		wally;
	double	texpos;
	int		tex_x;
	int		tex_y;
}			t_calc_wall;

typedef struct s_calc_dda
{
	float	camera_x;
	int		x;
	int		map_x;
	int		map_y;
}			t_calc_dda;

typedef struct s_calc_sprite
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_start_x;
	int		draw_end_y;
	int		draw_end_x;
	int		sprite_width;
	int		y;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		dir;
}			t_calc_sprite;

typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

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
	double	sprite_distance;
	double	z_buffer[SCREENWIDTH];
}			t_sprite;

typedef struct s_root {
	void			*mlx;
	void			*win;
	t_sprite		player;
	t_sprite		north_wall;
	t_sprite		south_wall;
	t_sprite		east_wall;
	t_sprite		west_wall;
	t_sprite		background;
	t_sprite		bar;
	t_sprite		mini_player;
	t_sprite		mini_wall;
	t_sprite		barrel;
	t_sprite		door;
	t_sprite		mini_door;
	char			**map;
	int				map_cols;
	int				map_lines;
	int				x;
	float			move_speed;
	float			rot_speed;
	t_ray			ray;
	t_calc_wall		calc_wall;
	t_calc_sprite	calc_sp;
	t_calc_dda		calc_dda;
	int				keys[9];
	int				c_color;
	int				f_color;
	char			init_dir;
}			t_root;

// PROTOTYPE

/* SETUP INIT */
void	init_values(t_root *game);
void	init_east(t_root *game);
void	init_west(t_root *game);
void	init_north(t_root *game);
void	init_south(t_root *game);

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
void	put_ray_to_img(t_sprite *dst, t_sprite src, int x, int y);
int		get_pixel_img(t_sprite img, int x, int y);
int		create_trgb(int t, int r, int g, int b);

/* DRAW */
void	draw_walls(t_root *game, int col);
void	draw_back(t_root *game);
void	draw_sprite(t_root *game);

/* MINIMAP */
void	draw_minimap(t_root *game);

/* UI */
void	check_mouse_lock(t_root *game);

/* HOOK HANDLERS */
int		input_release(int keycode, t_root *root);
int		input(int keycode, t_root *root);
int		mouse_input_release(int keycode, int x, int y, t_root *game);
int		mouse_input(int keycode, int x, int y, t_root *game);

/* EVENTS */
void	player_animation(t_root *game);
void	dda_calculation(t_root *game);
void	init_dda_values(t_root *game);
void	lenght_of_ray(t_root *game);
void	calculate_step(t_root *game);
void	jump_next_square(t_root *game);
void	open_door(t_root *game);
#endif