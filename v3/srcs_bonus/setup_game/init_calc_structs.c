/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_calc_structs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:47:50 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/27 14:15:19 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

static void	init_calc_dda(t_root *game)
{
	game->calc_dda.camera_x = 0;
	game->calc_dda.map_x = 0;
	game->calc_dda.map_y = 0;
	game->calc_dda.x = 0;
}

static void	init_calc_sprite(t_root *game)
{
	game->calc_sp.dir = 0;
	game->calc_sp.draw_end_x = 0;
	game->calc_sp.draw_end_y = 0;
	game->calc_sp.draw_start_x = 0;
	game->calc_sp.draw_start_y = 0;
	game->calc_sp.inv_det = 0;
	game->calc_sp.sprite_height = 0;
	game->calc_sp.sprite_screen_x = 0;
	game->calc_sp.sprite_width = 0;
	game->calc_sp.sprite_x = 0;
	game->calc_sp.sprite_y = 0;
	game->calc_sp.stripe = 0;
	game->calc_sp.tex_x = 0;
	game->calc_sp.tex_y = 0;
	game->calc_sp.transform_x = 0;
	game->calc_sp.transform_y = 0;
	game->calc_sp.y = 0;
}

static void	init_calc_wall(t_root *game)
{
	game->calc_wall.draw_end = 0;
	game->calc_wall.draw_start = 0;
	game->calc_wall.line_height = 0;
	game->calc_wall.map_x = 0;
	game->calc_wall.map_y = 0;
	game->calc_wall.tex_x = 0;
	game->calc_wall.tex_y = 0;
	game->calc_wall.texpos = 0;
	game->calc_wall.wallx = 0;
	game->calc_wall.draw_end = 0;
}

void	init_calc_structs(t_root *game)
{
	init_calc_dda(game);
	init_calc_sprite(game);
	init_calc_wall(game);
}
