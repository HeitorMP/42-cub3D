/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endswith.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:08:34 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/12 17:09:30 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_lib.h"

/// @brief check file name integrity
/// @param file_name
/// @return true if filename ends with ".cub"
int	ends_with(char *s1, char *s2)
{
	int	size_minus_four;

	if (!s1 || !s2)
		return (FALSE);
	size_minus_four = ft_strlen(s1) - ft_strlen(s2);
	return (ft_strncmp((s1 + size_minus_four), s2, ft_strlen(s2)) == 0);
}

int main()
{
	ft_printf("%d", ends_with("heitor.cub", ".cub"));
	ft_printf("%d", ends_with("heitor.cub", ".cub1"));
	ft_printf("%d", ends_with("heitor.cub", "1.cub"));
	return 0;
}

