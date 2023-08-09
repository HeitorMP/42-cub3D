/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:35:59 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/27 13:29:21 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

char	*ft_trim(const char *str)
{
	char		*result;
	const char	*end;
	size_t		size;
	size_t		i;

	if (!str)
		return (NULL);
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
		str++;
	if (*str == '\0')
		return (ft_calloc(sizeof(char), 1));
	end = str;
	while (*end)
		end++;
	end--;
	while (end >= str && ft_isspace(*end))
		end--;
	size = end - str + 1;
	result = ft_calloc(sizeof(char), size + 1);
	i = -1;
	while (++i < size)
		result[i] = str[i];
	return (result);
}
