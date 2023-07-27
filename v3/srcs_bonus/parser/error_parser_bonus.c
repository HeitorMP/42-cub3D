/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:13:56 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/27 13:30:22 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

int	ft_write_error(char *message)
{
	int	i;

	i = ft_strlen(message);
	write(1, "\033[0;34mError!\033[0\n", 18);
	write(1, message, i);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

int	ft_write_error_ext(char *message, char *extension)
{
	int	i;
	int	j;

	i = ft_strlen(message);
	j = ft_strlen(extension);
	write(1, "\033[0;34mError!\033[0\n", 18);
	write(1, message, i);
	write(1, extension, j);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}
