/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 03:54:07 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/20 03:54:07 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// int	empty_line(const char *str)
// {
// 	int	i;
// 	char c;

// 	i = 0;
// 	while (str[i])
// 	{
// 		c = str[i];
// 		if (!(c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' '))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static void ft_textures(t_file *file, char *filemap)
// {
// 	int		fd;
// 	char	*line;
// 	char	*temp;

// 	fd = open(filemap, O_RDONLY);
// 	if (fd == -1)
// 		ft_write_error("\033[0;34mMap not found!\033[0\n");
// 	line = get_next_line(fd);
// 	if (!line)
// 		ft_write_error("\033[0;34mEmpty map!\033[0\n");
// 	while (line != NULL)
// 	{
// 		temp = ft_trim(line);
// 		printf("temp %s", temp);
// 		// printf("\n");
// 		// printf("line %s", line);
// 		free(temp);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	while
// 	close(fd);
// }

static int ft_tiles(char **file, char *path, char *extension)
{
	// printf("%s\n", path);
	if (!*file)
	{
		*file = ft_strdup(path + 3);
		// printf("%s\n", *file);
		if (!*file)
		{
			// printf("teste\n");
			if(path)
				free(path);
			printf("\033[0;34mError allocation the file sprite!\033[0\n");
			return (1);
		}
		return (0);
	}
	else
		free(path);
	printf("\033[0;34mDetected double cardinal sprite! %s \033[0m", extension);
	return (1);
}

static int ft_textures(t_file *file, char *filemap)
{
	char	*line;
	char	*temp;

	temp = NULL;
	line = NULL;
	file->fd1 = open(filemap, O_RDONLY);
	if (file->fd1 == -1)
		return (printf("\033[0;34mError\nCouldn't open file!\033[0\n"));
	while (!file->no || !file->so || !file->we || !file->ea)
	{
		temp = get_next_line(file->fd1);
		if (!temp)
			break;
		// printf("%s\n", temp);
		line = ft_trim(temp);
		// printf("%s\n", line);
		free(temp);
		// printf("1 %d\n", ft_strncmp("WE ", line, 3));
		if (!ft_strncmp("NO ", line, 3) && ft_tiles(&(file->no), line, "NO"))
			return (1);
		if (!ft_strncmp("SO ", line, 3) && ft_tiles(&(file->so), line, "SO"))
			return (1);
		if (!ft_strncmp("WE ", line, 3) && ft_tiles(&(file->we), line, "WE"))
			return (1);
		if (!ft_strncmp("EA ", line, 3) && ft_tiles(&(file->ea), line, "EA"))
			return (1);
		free(line);
	}
	// printf("file no %s\n", file->no);
	// printf("file so %s\n", file->so);
	// printf("file we %s\n", file->we);
	// printf("file ea %s\n", file->ea);
	if (ft_checktile(file->no, ".xpm") || ft_checktile(file->so, ".xpm") || ft_checktile(file->we, ".xpm") || ft_checktile(file->ea, ".xpm"))
		return (1);
	// printf("file no %s\n", file->no);
	// printf("file so %s\n", file->so);
	// printf("file we %s\n", file->we);
	// printf("file ea %s\n", file->ea);
	// printf("\033[0;34mTiles OK!!!\033[0\n");
	return (0);
}

static int	ft_checkmap(char *filemap)
{
	int		fd;
	char	*line;

	fd = open(filemap, O_RDONLY);
	if (fd == -1)
		return (printf("\033[0;34mError\nCouldn't open file!\033[0\n"));
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		close(fd);
		return (printf("\033[0;34mError\nEmpty map!\033[0\n"));
	}
	free(line);
	close(fd);
	return (0);
}

static int init_file(t_file *file)
{
	file->ceilling.blue= -1;
	file->ceilling.green = -1;
	file->ceilling.red = -1;
	file->floor.red = -1;
	file->floor.green = -1;
	file->floor.blue = -1;
	file->rows = 0;
	file->x = -1;
	file->y = -1;
	file->x0 = -1;
	file->y0 = -1;
	file->no = NULL;
	file->so = NULL;
	file->we = NULL;
	file->ea = NULL;
	file->map = NULL;
	file->fd1 = -1;
	file->fd2 = -1;
	file->fd3 = -1;
	return (0);
}

int ft_parser(t_file *file, char *filemap)
{
	if (init_file(file) || ft_checkmap(filemap))
		return (1);
	if (ft_textures(file, filemap) || ft_colors(file, filemap))
		return (1);
	if (ft_maps(file, filemap))
		return (1);
	return (0);
}