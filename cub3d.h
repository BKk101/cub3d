#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>


typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_mapinfo
{
	int			info_flag[8]; // r, no, so, we, ea, s, f, c
	int			win_wid;
	int			win_hei;
	char		*path_list[5]; // NO,SO,WE,EA,S
	int			fc_rgb[2][3]; // F, C
	int			row;
	int			col;
	int			**arr;
	double		posX;
	double		posY;
}				t_mapinfo;

typedef struct  s_vars {
    void        *mlx;
    void        *win;
	int			color;
	clock_t		str_time;
	double		elp_time;
	t_img		img_pic;
	t_img		img_map;
	t_mapinfo	map_info;
}               t_vars;

int		read_mapfile(t_mapinfo *map_info, const char *map_path);
void	free_dptr(char **start, int len);
int		raycast(t_vars *vars);

#endif