#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/includes/libft.h"

/* KEY MACROS */
# define ESC 65307
# define RIGHT 100
# define LEFT 97
# define UP 119
# define DOWN 115
# define NONE 0


# define PI 3.1415926535

typedef struct	s_sprite {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	float	x_pos;
	float	y_pos;
	float	delta_x;
	float	delta_y;
	float	angle;
}				t_sprite;

typedef struct	s_root {
	void		*mlx;
	void		*win;
	t_sprite	player;
	t_sprite	mini_background;
}				t_root;

// PROTOTYPE
int	exit_game_request(t_root *root);

#endif