/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:13:28 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/21 16:33:27 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/* invert x y to correct moving walls*/
static float	calc_wall_wall_x(t_root *game)
{
	float	tmp_wallx;

	if (game->ray.side == 0)
		tmp_wallx = game->player.x_pos + \
		game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		tmp_wallx = game->player.y_pos + game->ray.perp_wall_dist * \
		game->ray.ray_dir_x;
	tmp_wallx -= floor((tmp_wallx));
	return (tmp_wallx);
}

static int	fix_inverted_x(t_root *game, int tex_x)
{
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		return (IMGSIZE - tex_x - 1);
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0) 
		return (IMGSIZE - tex_x - 1);
	return (tex_x);
}

static void	init_calc_wall_walls(t_root *game)
{
	game->calc_wall.wallx = calc_wall_wall_x(game);
	game->calc_wall.tex_x = (int)(game->calc_wall.wallx * (double)(IMGSIZE));
	game->calc_wall.texpos = (game->calc_wall.draw_start - SCREENHEIGHT / 2 + \
		game->calc_wall.line_height / 2) * (1.0 * IMGSIZE / \
		game->calc_wall.line_height);
	game->calc_wall.wally = game->calc_wall.draw_start;
	game->calc_wall.tex_x = fix_inverted_x(game, game->calc_wall.tex_x);
}

void	draw_walls(t_root *game, int col)
{
	init_calc_wall_walls(game);
	while (game->calc_wall.wally < game->calc_wall.draw_end)
	{
		game->calc_wall.tex_y = (int)game->calc_wall.texpos & (IMGSIZE - 1);
		game->calc_wall.texpos += (1.0f * IMGSIZE / \
			game->calc_wall.line_height);
		if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
			my_mlx_pixel_put(&game->background, col, game->calc_wall.wally, \
			get_pixel_img(game->south_wall, game->calc_wall.tex_x, \
			game->calc_wall.tex_y));
		else if (game->ray.side == 0 && game->ray.ray_dir_x < 0)
			my_mlx_pixel_put(&game->background, col, game->calc_wall.wally, \
			get_pixel_img(game->north_wall, game->calc_wall.tex_x, \
			game->calc_wall.tex_y));
		else if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
			my_mlx_pixel_put(&game->background, col, game->calc_wall.wally, \
			get_pixel_img(game->west_wall, game->calc_wall.tex_x, \
			game->calc_wall.tex_y));
		else
			my_mlx_pixel_put(&game->background, col, game->calc_wall.wally, \
			get_pixel_img(game->east_wall, game->calc_wall.tex_x, \
			game->calc_wall.tex_y));
		game->calc_wall.wally++;
	}
}
