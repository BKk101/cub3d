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
# include <errno.h>

# define PLANE 0.66

typedef struct	s_pos_int {
	int 		x;
	int 		y;
}				t_pos_int;

typedef struct	s_pos_doub {
	double 		x;
	double 		y;
}				t_pos_doub;

typedef struct	s_texture {
	int			*data;
	t_pos_int	size;
}				t_texture;

typedef struct	s_sprite {
	int			tex_num;
	t_pos_doub	pos;
}				t_sprite;

typedef struct	s_map {
	int			**data;
	t_pos_int	size;
}				t_map;

typedef struct	s_window {
	int			**scene;
	int			wid;
	int			hei;
}				t_window;

typedef struct	s_ray{
	int			side;
	t_pos_int	map;
	t_pos_doub	dir;
}				t_ray;

typedef struct	s_player
{
	char 		key;
	double		time;
	double		movespeed;
	double		rotspeed;
	t_pos_doub	pos;
	t_pos_doub	dir;
	t_pos_doub	plane;
}				t_player;

typedef struct	s_mlx {
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;
	int			bpp;
	int			sl;
	int			endian;
}				t_mlx;

typedef struct	s_vars {
	int			f_rgb[3];
	int			c_rgb[3];
	double		*zbuf;
	t_window	window;
	t_player	player;
	t_texture	texture[5];
	t_list		*sprite;
	t_map		map;	
}				t_vars;

typedef struct	s_mapinfo {
	char		news; //start dir
	char		*path_list[5]; // NO,SO,WE,EA,S
	int			fc_rgb[2][3]; // F, C
	int			**map;
	t_pos_int	win; //resolution
	t_pos_int	rc; //array row,col
	t_pos_doub	pos; //player start pos
}				t_mapinfo;

typedef struct	s_wallinfo{
	int		line_h;
	int		draw_s;
	int		draw_e;
	int		tex_n;
	int		tex_w;
	int		tex_h;
	int		tex_x;
	double	perp_wall_dist;
	double	wall_x;
	double	step;
	double	tex_pos;
	t_ray	ray;
}				t_wallinfo;

typedef struct	s_sprinfo{
	int				w;
	int				h;
	int				sprite_screen_x;
	int				sprite_h;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_w;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_width;
	int				tex_height;
	int				tex_x;
	int				tex_y;
	int				d;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	unsigned int	color;
}				t_sprinfo;

extern	t_mlx		g_mlx;
extern	t_mapinfo	g_mapinfo;
extern	t_vars		g_vars;

int		Read_mapfile(t_mapinfo *m_info, char *map_path);
void	free_dptr(char **start, int len);
int Key_press(int keycode, t_vars *vars);
int Key_release(int keycode, t_vars *vars);
int Mouse(int button, int x, int y, t_vars *vars);
int	Exit(int vars);
void Rotate(t_pos_doub *vec, t_player *player);
void Move(int **map, t_player *player);
void Move2(int **map, t_player *player);

t_ray	init_ray(t_player player, int x, int w);
double	calc_perp_wall_dist(t_vars *vars, t_ray *ray);
t_pos_doub	calc_side_dist(t_ray ray, t_pos_doub delta_dist, double pos_x, double pos_y);
t_pos_int		calc_step(t_ray ray);
t_pos_doub	calc_delta_dist(t_ray ray);
void	draw_wall(t_vars *vars);
void	draw_background(t_window *window, int *floor, int *ceil);
void	draw_sprite(t_vars *vars);
int	init_data(void);
void	update_player(int **map, t_player *player);
void	update_scene(void);
void	redraw(t_mlx mlx);
int		Error(char *s);
int	load_texture(t_texture *texture, char *file_path);

int ft_max(int a, int b);
int ft_min(int a, int b);
void	save_bmp(t_window win);

#endif