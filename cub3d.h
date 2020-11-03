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
#define PLANE 0.66


typedef struct	s_pos_int {
	int 		x;
	int 		y;
}				t_pos_int;

typedef struct	s_pos_doub {
	double 		x;
	double 		y;
}				t_pos_doub;

typedef struct	s_mapinfo {
	char		news;
	char		*path_list[5]; // NO,SO,WE,EA,S
	int			fc_rgb[2][3]; // F, C
	int			**map;
	t_pos_int	win;
	t_pos_int	rc;
	t_pos_doub	pos;
}				t_mapinfo;

typedef struct	s_rayinfo {
	char key;
	double frameTime;
	double moveSpeed;
	double rotSpeed;
	t_pos_doub	dir;
	t_pos_doub	plane;
}				t_rayinfo;

typedef struct	s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	int		bpp;
	int		sl;
	int		endian;
}				t_mlx;

typedef struct	s_vars {
	t_mlx	*mlx;
	t_mapinfo	*m_info;
	t_rayinfo	*r_info;	
}			t_vars;

extern	t_mlx		g_mlx;
extern	t_mapinfo	g_mapinfo;
extern	t_rayinfo	g_rayinfo;
extern	t_vars		g_vars;
extern const unsigned int wall1[];

int		Read_mapfile(t_mapinfo *m_info, const char *map_path);
void	free_dptr(char **start, int len);
int		Raycast(t_vars *vars);
int	Keyboard(int keycode, t_vars *vars);
int Mouse(int button, int x, int y, t_vars *vars);
void Rotate(t_pos_doub *s, char dir);
void Move(t_pos_doub *pos, char dir);
void Move2(t_pos_doub *pos, char dir);
double Calc_step_sidedist(double ray, double pos, int *step, double *sideDist);
int DDA(t_pos_doub *sideDist, t_pos_int *map, t_pos_doub deltDist, t_pos_int step, t_pos_doub ray);

#endif