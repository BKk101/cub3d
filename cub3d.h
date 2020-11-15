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

typedef struct		s_pos_int {
	int				x;
	int				y;
}					t_pos_int;

typedef struct		s_pos_doub {
	double			x;
	double			y;
}					t_pos_doub;

typedef struct		s_texture {
	int				*data;
	t_pos_int		size;
}					t_texture;

typedef struct		s_sprite {
	int				tex_num;
	t_pos_doub		pos;
}					t_sprite;

typedef struct		s_map {
	char			**data;
	t_pos_int		size;
}					t_map;

typedef struct		s_window {
	int				**scene;
	int				wid;
	int				hei;
}					t_window;

typedef struct		s_ray{
	int				side;
	t_pos_int		map;
	t_pos_doub		dir;
}					t_ray;

typedef struct		s_player
{
	char			key;
	double			time;
	double			movespeed;
	double			rotspeed;
	t_pos_doub		pos;
	t_pos_doub		dir;
	t_pos_doub		plane;
}					t_player;

typedef struct		s_mlx {
	void			*mlx;
	void			*win;
	void			*img;
	int				*data;
	int				bpp;
	int				sl;
	int				endian;
}					t_mlx;

typedef struct		s_vars {
	int				f_rgb[3];
	int				c_rgb[3];
	double			*zbuf;
	t_window		window;
	t_player		player;
	t_texture		texture[5];
	t_list			*sprite;
	t_map			map;
}					t_vars;

typedef struct		s_mapinfo {
	char			news;
	char			**map;
	char			*elem[10];
	char			*path_list[5];
	int				elem_num;
	int				fc_rgb[2][3];
	t_pos_int		win;
	t_pos_int		rc;
	t_pos_doub		pos;
}					t_mapinfo;

typedef struct		s_wallinfo{
	int				line_h;
	int				draw_s;
	int				draw_e;
	int				tex_n;
	int				tex_w;
	int				tex_h;
	int				tex_x;
	double			pwall_dist;
	double			wall_x;
	double			step;
	double			tex_pos;
	t_ray			ray;
}					t_wallinfo;

typedef struct		s_sprinfo{
	int				w;
	int				h;
	int				d;
	int				sprite_w;
	int				sprite_h;
	int				sprite_screen_x;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				tex_width;
	int				tex_height;
	int				tex_x;
	int				tex_y;
	double			inv_det;
	double			sprite_x;
	double			sprite_y;
	double			transform_x;
	double			transform_y;
	unsigned int	color;
}					t_sprinfo;

extern	t_mlx		g_mlx;
extern	t_mapinfo	g_mapinfo;
extern	t_vars		g_vars;

int					Read_mapfile(t_mapinfo *m_info, char *map_path);

int					init_data(void);
char				**init_map(char **strs, t_pos_int size);
void				init_mapdata(t_mapinfo *m_info);
void				save_bmp(t_window win);
void				update_player(char **map, t_player *player);
void				update_scene(void);
void				redraw(t_mlx mlx);

int					Key_press(int keycode, t_vars *vars);
int					Key_release(int keycode, t_vars *vars);
int					Mouse(int button, int x, int y, t_vars *vars);
int					Exit(int vars);

double				calc_pwall_dist(t_vars *vars, t_ray *ray);
t_ray				init_ray(t_player player, int x, int w);
t_pos_int			calc_step(t_ray ray);
t_pos_doub			calc_side_dist(t_ray ray, t_pos_doub pos);
t_pos_doub			calc_delta_dist(t_ray ray);

void				draw_wall(t_vars *vars);
void				draw_background(t_window *window, int *floor, int *ceil);
void				draw_sprite(t_vars *vars);
void				Rotate(t_pos_doub *vec, t_player *player);
void				Move(char **map, t_player *player);
void				Move2(char **map, t_player *player);

int					valid_map(t_mapinfo *m_info, int *flag);
int					valid_elem(t_mapinfo *m_info, int *flag);

int					Error(char *s);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
int					ft_dptrlen(char **dptr);
int					count_chars(const char *s, int c);
int					is_all_digit(const char *s);
void				free_dptr(char **start, int len);
void				sort_list(t_list *start, int (*cmp)());


#endif
