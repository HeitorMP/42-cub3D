/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:39:05 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/21 15:47:40 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_calc_sprite(t_root *game)
{
	game->barrel.sprite_distance = ((game->player.y_pos - game->barrel.y_pos) \
	* (game->player.y_pos - game->barrel.y_pos) + (game->player.x_pos - \
	game->barrel.x_pos) * (game->player.x_pos - game->barrel.x_pos));
	game->calc_sp.sprite_x = game->barrel.y_pos - game->player.y_pos;
	game->calc_sp.sprite_y = game->barrel.x_pos - game->player.x_pos;
	game->calc_sp.inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - \
	game->player.dir_x * game->player.plane_y);
	game->calc_sp.transform_x = game->calc_sp.inv_det * \
	(game->player.dir_y * game->calc_sp.sprite_x - \
	game->player.dir_x * game->calc_sp.sprite_y);
	game->calc_sp.transform_y = game->calc_sp.inv_det * \
	(-game->player.plane_y * game->calc_sp.sprite_x + game->player.plane_x \
	* game->calc_sp.sprite_y);
	game->calc_sp.sprite_screen_x = (int)((SCREENWIDTH / 2) * \
	(1 + game->calc_sp.transform_x / game->calc_sp.transform_y));
	game->calc_sp.sprite_height = abs((int)(SCREENHEIGHT / \
	(game->calc_sp.transform_y))); 
}

static void	find_y_values(t_root *game)
{
	game->calc_sp.draw_start_y = -game->calc_sp.sprite_height / 2 + \
		SCREENHEIGHT / 2;
	game->calc_sp.draw_end_y = game->calc_sp.sprite_height / 2 + \
		SCREENHEIGHT / 2;
	if (game->calc_sp.draw_start_y < 0)
		game->calc_sp.draw_start_y = 0;
	if (game->calc_sp.draw_end_y >= SCREENHEIGHT)
		game->calc_sp.draw_end_y = SCREENHEIGHT - 1;
}

static void	find_x_values(t_root *game)
{
	game->calc_sp.sprite_width = abs((int)(SCREENHEIGHT / \
		(game->calc_sp.transform_y)));
	game->calc_sp.draw_start_x = -game->calc_sp.sprite_width \
		/ 2 + game->calc_sp.sprite_screen_x;
	if (game->calc_sp.draw_start_x < 0)
		game->calc_sp.draw_start_x = 0;
	game->calc_sp.draw_end_x = game->calc_sp.sprite_width \
		/ 2 + game->calc_sp.sprite_screen_x;
	if (game->calc_sp.draw_end_x >= SCREENWIDTH)
		game->calc_sp.draw_end_x = SCREENWIDTH - 1;
}

static void	do_sprite_print(t_root *game)
{
	game->calc_sp.dir = (game->calc_sp.y) * 256 - \
		SCREENHEIGHT * 128 + game->calc_sp.sprite_height * 128;
	game->calc_sp.tex_y = ((game->calc_sp.dir * IMGSIZE) \
		/ game->calc_sp.sprite_height) / 256;
	my_mlx_pixel_put(&game->background, game->calc_sp.stripe, \
		game->calc_sp.y, get_pixel_img(game->barrel, \
		game->calc_sp.tex_x, game->calc_sp.tex_y));
}

void	draw_sprite(t_root *game)
{
	init_calc_sprite(game);
	find_y_values(game);
	find_x_values(game);
	game->calc_sp.stripe = game->calc_sp.draw_start_x;
	while (game->calc_sp.stripe < game->calc_sp.draw_end_x)
	{
		game->calc_sp.tex_x = (int)(256 * (game->calc_sp.stripe - \
		(-game->calc_sp.sprite_width / 2 + game->calc_sp.sprite_screen_x)) \
		* IMGSIZE / game->calc_sp.sprite_width) / 256;
		if (game->calc_sp.transform_y > 0 && game->calc_sp.stripe > 0 \
		&& game->calc_sp.stripe < SCREENWIDTH && \
		game->calc_sp.transform_y < game->barrel.z_buffer[game->calc_sp.stripe])
		{
			game->calc_sp.y = game->calc_sp.draw_start_y;
			while (game->calc_sp.y < game->calc_sp.draw_end_y)
			{
				do_sprite_print(game);
				game->calc_sp.y++;
			}
		}
		game->calc_sp.stripe++;
	}
}
