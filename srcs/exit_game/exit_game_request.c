/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game_request.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:39:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/06/07 15:02:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	exit_game_request(t_root *root)
{
	mlx_clear_window(root->mlx, root->win);
	mlx_destroy_window(root->mlx, root->win);
	mlx_destroy_display(root->mlx);
	free(root->mlx);
	printf("Good bye and thanks for playing!!\n");
	exit (0);
	return (0);
}