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

typedef struct	s_pos_int
{
	int 		x;
	int 		y;
}				t_pos_int;

typedef struct	s_pos_doub
{
	double 		x;
	double 		y;
}				t_pos_doub;

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
	char		*path_list[5]; // NO,SO,WE,EA,S
	int			fc_rgb[2][3]; // F, C
	int			**map;
	t_pos_int	win;
	t_pos_int	rc;
	t_pos_doub	pos;
}				t_mapinfo;

typedef struct	s_rayinfo
{
	double time; //time of current frame
	double oldTime; //time of previous frame
	double frameTime;
	double moveSpeed;
	double rotSpeed;
	t_pos_doub	dir;
	t_pos_doub	plane;
}				t_rayinfo;

typedef struct  s_vars {
    void        *mlx;
    void        *win;
	int			color;
	clock_t		str_time;
	double		elp_time;
	t_img		img_pic;
	t_img		img_map;
	t_mapinfo	map_info;
	t_rayinfo	ray_info;
}               t_vars;

int		read_mapfile(t_mapinfo *m_info, const char *map_path);
void	free_dptr(char **start, int len);
int		raycast(t_vars *vars);

#endif