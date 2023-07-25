/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:13:56 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/19 20:13:56 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_write_error(char *message)
{
	ft_putstr_fd("\033[0;34mError!\033[0\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

int	ft_ft_putstr_fd_error_ext(char *message, char *extension)
{
	ft_putstr_fd("\033[0;34mError!\033[0\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(extension, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}