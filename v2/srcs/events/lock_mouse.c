/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:03:12 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/18 13:27:58 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_mouse_lock(t_root *game)
{
	if (game->keys[6] != -1)
		mlx_mouse_move(game->mlx, game->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
}
