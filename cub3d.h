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
	int			info_list[8]; // r, no, so, we, ea, s, f, c
	int			wid;
	int			hei;
	char		*path_list[5]; // NO,SO,WE,EA,S
	int			rgb[2][3]; // F, C
	
}				t_map;

typedef struct	s_map2d
{
	int col;
	int row;
	int **arr;
}				t_map2d;

int map_read(t_map *map_info, t_map2d *map, const char *map_path);
void	free_dptr(char **start, int len);

#endif