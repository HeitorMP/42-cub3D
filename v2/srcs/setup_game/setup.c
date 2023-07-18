/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:33:21 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/17 16:36:37 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_values(t_root *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		game->keys[i] = 0;
		i++;
	}
	game->keys[6] = -1;
}