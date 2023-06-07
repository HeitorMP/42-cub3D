/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:31:12 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/06/07 15:00:07 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	turn_left(t_root *root)
{
	root->player.angle -= 0.1;
	if (root->player.angle < 0)
	{
		root->player.angle += 2 * PI;
	}
	root->player.delta_x = cos(root->player.angle) * 5;
	root->player.delta_y = sin(root->player.angle) * 5;
}

void	turn_right(t_root *root)
{
	root->player.angle += 0.1;
	if (root->player.angle > 2 * PI)
	{
		root->player.angle -= 2 * PI;
	}
	root->player.delta_x = cos(root->player.angle) * 5;
	root->player.delta_y = sin(root->player.angle) * 5;
}