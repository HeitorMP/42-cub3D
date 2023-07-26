/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:20:13 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/21 22:20:13 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int rgb_color_parser(char *str)
{
	int num;
	int i;

	i = 0;
	num = 0;
	if (!str)
		return (-2);
	// printf("num str %s\n", str);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10;
		num += str[i] - 48;
		i++; 
	}
	// printf("num %d\n", num);
	// printf("str i %c\n", str[i]);
	if (str[i] && str[i] != ',')
		return (-2);
	if (i && (num >= 0 && num <= 255))
		return (num);
	return (-1);
}

static int parse_colors(t_rgb *rgb, char *str)
{
	char *temp;

	temp = str;
	if (*str && *str == ',')
		str++;
	rgb->red = rgb_color_parser(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str && *str == ',')
		str++;
	rgb->green = rgb_color_parser(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str && *str == ',')
		str++;
	rgb->blue = rgb_color_parser(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	// printf("num red %d\n", rgb->red);
	// printf("num green %d\n", rgb->green);
	// printf("num blue %d\n", rgb->blue);
	// printf("*str 1 %c\n", *str);
	if (!*str && rgb->red >= 0 && rgb->red <= 255 && rgb->green >= 0 && \
		rgb->green <= 255 && rgb->blue >= 0 && rgb->blue <= 255)
	{
		free (temp);
		return (0);
	}
	free (temp);
	return (1);
}

int ft_colors(t_file *file, char *filemap)
{
	int c;
	int f;
	char *temp;
	char *line;

	c = 1;
	f = 1;
	file->fd2 = open(filemap, O_RDONLY);
	if (file->fd2 == -1)
		return (printf("\033[0;34mError\nCouldn't open file!\033[0\n"));
	while (c || f)
	{
		temp = get_next_line(file->fd2);
		if (!temp)
			break;
		// printf("%s\n", temp);
		line = ft_trim(temp);
		// printf("%s\n", line);
		free(temp);
		if (f && ft_strlen(line) > 2 && line[0] == 'F' && line[1] == ' ')
			f = parse_colors(&file->floor, ft_strdup(line + 2));
		if (c && ft_strlen(line) > 2 && line[0] == 'C' && line[1] == ' ')
			c = parse_colors(&file->ceilling, ft_strdup(line + 2));
		free(line);
	}
	// printf("num floor red %d\n", file->floor.red);
	// printf("num floor green %d\n", file->floor.green);
	// printf("num floor blue %d\n", file->floor.blue);
	// printf("num ceiling red %d\n", file->ceilling.red);
	// printf("num ceiling green %d\n", file->ceilling.green);
	// printf("num ceiling blue %d\n", file->ceilling.blue);
	if (c)
		return (printf("\033[0;34mError\nIn ceiling colors!\033[0\n"));
	if (f)
		return (printf("\033[0;34mError\nIn floor colors!\033[0\n"));
	return (0);
}