/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:44:58 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/27 13:29:48 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

char	*ft_strdup_cub(const char *str)
{
	int		i;
	char	*dest;

	if (!str)
		return (NULL);
	i = 0;
	dest = (char *)malloc((ft_strlen(str) + 1));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_checkfile(char *filemap, char *extension)
{
	size_t	i;
	size_t	j;
	int		len_file;
	char	ext[4];

	i = 4;
	j = 0;
	len_file = ft_strlen(filemap);
	while (i > 0)
	{
		ext[j] = filemap[len_file - i];
		j++;
		i--;
	}
	if (ft_strncmp(extension, ext, 4) != 0)
	{
		write(1, "\033[0;34mError!\033[0\n", 18);
		write(1, "\033[0;34mInvalid map extension!\033[0\n", 34);
		return (1);
	}
	return (0);
}

int	ft_checktile_ext(char *filemap, char *extension)
{
	size_t	i;
	size_t	j;
	int		len_file;
	char	ext[4];

	i = 4;
	j = 0;
	len_file = ft_strlen(filemap);
	while (i > 0)
	{
		ext[j] = filemap[len_file - i];
		j++;
		i--;
	}
	if (ft_strncmp(extension, ext, 4) != 0)
	{
		write(1, "\033[0;34mError!\033[0\n", 18);
		write(1, "\033[0;34mInvalid tile extension!\033[0\n", 34);
		return (1);
	}
	return (0);
}

int	ft_checktile(char *filemap, char *extension)
{
	int	fd;

	if (!filemap)
		return (printf("\033[0;34mNULL file path! EXPECTED: \
			'*%s'\033[0\n", extension));
	if (ft_checktile_ext(filemap, extension))
		return (1);
	fd = open(filemap, O_RDONLY);
	if (fd == -1)
		return (printf("\033[0;34mError!\nTile not found!\033[0\n"));
	close(fd);
	return (0);
}

int	check_path(int argc, char **argv)
{
	if (argc < 2)
		ft_write_error("\033[0;34mMap not found!\033[0");
	else if (argc > 2)
		ft_write_error("\033[0;34mToo many arguments!\033[0");
	if (ft_checkfile(argv[1], ".cub"))
		return (1);
	return (0);
}
