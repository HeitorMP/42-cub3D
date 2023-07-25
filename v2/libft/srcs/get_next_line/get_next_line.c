/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:26:03 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/25 16:30:58 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"


char *get_next_line(int fd)
{
	char *b = (char *)malloc(sizeof(char) * 10000), *y = b;
	while (read(fd, y, 1) > 0 && *y++ != '\n');
	return y > b ? (*y = 0, b) : (free(b), NULL);
}