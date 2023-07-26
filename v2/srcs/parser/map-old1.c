/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-old1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:46:04 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/26 16:12:04 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_get_map(t_file *file, int size)
{
	char	*temp;
	int		result;

	temp = get_next_line(file->fd3);
	result = 0;
	while (size == 0 && empty_line(temp))
	{
		free(temp);
		temp = get_next_line(file->fd3);
	}
	if (!temp)
	{
		file->map = malloc(sizeof(char *) * (size + 1));
		// printf("%d\n", size);
		file->rows = size;
		if (!file->map)
			return (1);
	}
	else
		result = ft_get_map(file, (size + 1));
	if (result)
		free(temp);
	else
		file->map[size] = temp;
	return (result);
}

static int map_rows(t_file *file, char *filemap)
{
	int i;
	int rows;
	char *line;

	i = 0;
	rows = 0;
	line  = NULL;
	file->fd3 = open(filemap, O_RDONLY);
	if (file->fd3 == -1)
		return (printf("\033[0;34mError\nCouldn't open file!\033[0\n"));
	line = get_next_line(file->fd3);
	while (i < 6)
	{
		if (!empty_line(line))
			i += 1;
		free(line);
		line = get_next_line(file->fd3);
	}
	rows = ft_get_map(file, 0);
	free (line);
	return (rows);
}

// static char	**get_map_part(char *file_name, int scene_fd)
// {
// 	size_t	i;
// 	size_t	nbr_lines;
// 	char	**map;
// 	char	*line;

// 	nbr_lines = get_nbr_map_lines(file_name);
// 	map = malloc((nbr_lines + 1) * sizeof(char *));
// 	i = 0;
// 	while (i < nbr_lines)
// 	{
// 		line = trim_free(get_next_line(scene_fd), "\n");
// 		map[i] = line;
// 		i += 1;
// 	}
// 	map[i] = NULL;
// 	return (map);
// }

// bool	is_onstr(const char *str, int ch)
// {
// 	size_t	i;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ch)
// 			return (true);
// 		i += 1;
// 	}
// 	return (false);
// }

int ft_maps(t_file *file, char *filemap)
{
	int i;
	int result;

	i = -1;
	// result = 0;
	(void)file;
	result = map_rows(file, filemap);
	while (file->map[++i])
	{
		printf("linha %i - %s\n", i, file->map[i]);
	}
	if (ft_count_player(file, file->map))
		return (1);
	printf("result %d\n", result);
	// printf("rows %d\n", file->rows);
	printf("x player %d\n", file->x);
	printf("y player %d\n", file->y);
	return (0);
}