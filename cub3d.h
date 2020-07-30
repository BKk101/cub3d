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

int map_read(const char *map_path);

#endif