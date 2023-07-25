/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:35:59 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/20 20:35:59 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char *ft_trim(const char *str)
{
	char *result;
	const char *end;
	size_t	size;
	size_t	i;

    if (!str)
        return NULL;
    while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
        str++;
    if (*str == '\0')
    {
        char *result = malloc(1);
        if (result)
            result[0] = '\0';
        return (result);
    }
    end = str;
    while (*end)
        end++;
    end--;
    while (end >= str && ft_isspace(*end))
    	end--;
    size = end - str + 1;
    result = malloc(size + 1);
    if (!result)
        return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = str[i];
		i++;
	}
    result[size] = '\0';
    return (result);
}
