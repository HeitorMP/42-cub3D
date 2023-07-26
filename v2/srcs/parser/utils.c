/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:13:16 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/23 17:13:16 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/*No linux terei que retirar a função ft_issapce*/
int	valid_char(char c)
{
	if (c == '0' || c == ' ' || c == '1' || is_player(c) || c == 'D' || ft_isspace(c))
		return (0);
	return (1);
}

int	ft_isspace(int c)
{
		if (c != '\f' && c != '\n' && c != '\r' && c != '\t'\
			&& c != '\v' && c != ' ')
			return (0);
	return (1);
}

int	empty_line(char *str)
{
	int	i;
	char c;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		c = str[i];
		if (!(c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' '))
			return (0);
		i++;
	}
	return (1);
}