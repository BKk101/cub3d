#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
	void		*img;
	int			color;
	clock_t		start;
	double		elapsed;

}               t_vars;

typedef struct	s_map
{
	int			r;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			s;
	int			f;
	int			c;
	int			wid;
	int			hei;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*s_path;
	int			f_rgb[3];
	int			c_rgb[3];
	
}				t_map;

int map_read(const char *map_path);

#endif