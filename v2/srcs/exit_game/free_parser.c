/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:16:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/25 10:36:57 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_sfile(t_file *file)
{
	char	**temp;

	if (file->map)
	{
		temp = file->map;
		while (*file->map)
			free(*(file->map++));
		free(temp);
	}
	if (file->ea)
		free(file->ea);
	if (file->no)
		free(file->no);
	if (file->so)
		free(file->so);
	if (file->we)
		free(file->we);
	if (file->fd1 != -1)
		close(file->fd1);
	if (file->fd2 != -1)
		close(file->fd2);
	if (file->fd3 != -1)
		close(file->fd3);
}