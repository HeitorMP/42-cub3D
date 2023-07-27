/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 08:30:48 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/07/27 13:39:32 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_file
{
	int		fd1;
	int		fd2;
	int		fd3;
	int		rows;
	int		x;
	int		x0;
	int		y;
	int		y0;
	char	orientation;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_rgb	floor;
	t_rgb	ceilling;
	char	**map;
	int		enemy_x;
	int		enemy_y;
	int		has_enemy;
}	t_file;

typedef struct s_coord
{
	int x;
	int y;
}			t_coord;

/* CHECK FILE */

int		check_path(int argc, char **argv);
int		ft_checkfile(char *filemap, char *extension);
char	*ft_strdup_cub(const char *str);
int		ft_checktile(char *filemap, char *extension);
int		ft_checktile_ext(char *filemap, char *extension);
int		check_enemy(t_file *file, char **map);

/* COLORS */

int		ft_colors(t_file *file, char *filemap);

/* ERROR PARSER */

int		ft_write_error(char *message);
int		ft_write_error_ext(char *message, char*extension);

/* MAP UTILS */

int 	player_pos(t_file *file, char **map);
char	*ft_trim_end(const char *str);
int		ft_count_player(t_file *file, char **map);

/* MAP */

int		find_zero(t_file *file, char **map);
int		ft_maps(t_file *file, char *filemap);
int		checkmap(t_file *file, char **map);

/* PARSER UTILS */

char	*ft_trim(const char *str);

/* PARSER */

int		ft_parser(t_file *file, char *filemap);

/* UTILS */

int		ft_isspace(int c);
int		is_player(char c);
int		valid_char(char c);
int		empty_line(char *str);

/*mtr_utils*/
int		mtr_len(char **matriz);
void	mtr_free(char **matriz);
char	**mtr_dup(char **matriz);
char	**mtr_addnew(char *str, char **matrizold);
char	**mtr_rmv(int pos, char **matrizold);

/* ENEMY */
int		check_enemy(t_file *file, char **map);

#endif