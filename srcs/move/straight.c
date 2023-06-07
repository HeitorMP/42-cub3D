/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:36:35 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/06/07 15:00:09 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_root *root)
{
	root->player.x_pos += root->player.delta_x;
	root->player.y_pos += root->player.delta_y;
}

void	move_backward(t_root *root)
{
	root->player.x_pos -= root->player.delta_x;
	root->player.y_pos -= root->player.delta_y;
}