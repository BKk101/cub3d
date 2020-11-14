#include "./cub3d.h"

t_pos_doub	g_dir[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
t_pos_doub	g_plane[4] = {{PLANE, 0}, {-PLANE, 0}, {0, -PLANE} ,{0, PLANE}};
static char	g_news[4] = "NSWE";

int		init_sprite(t_list **head, t_map map)
{
	int			i;
	int			j;
	t_sprite	*p;

	i = -1;
	while (++i < map.size.y)
	{
		j = -1;
		while (++j < map.size.x)
			if (map.data[i][j] == 2)
			{
				p = malloc(sizeof(t_sprite));
				p->pos.x = 0.5 + j;
				p->pos.y = 0.5 + i;
				p->tex_num = 4;
				ft_lstadd_back(head, ft_lstnew((void*)p));
			}
	}
	return (1);
}

int		init_texture(t_vars *vars, char **path)
{
	int ret;
	int i;

	i = -1;
	while (++i<5)
	{
		ret = load_texture(&vars->texture[i], path[i]);
	}
	//if (!ret)
		//print_error(cuberror(invlid_texture_file));
	return (ret);
}

void	init_window(void)
{
	int i;

	g_mapinfo.win.x = ft_min(g_mapinfo.win.x, 1920);
	g_mapinfo.win.x = ft_max(g_mapinfo.win.x, 400);
	g_mapinfo.win.y = ft_min(g_mapinfo.win.y, 1080);
	g_mapinfo.win.y = ft_max(g_mapinfo.win.y, 300);
	if ((double)g_mapinfo.win.x/g_mapinfo.win.y > 2.5)
		g_mapinfo.win.x = g_mapinfo.win.y * 4 / 3;
	if ((double)g_mapinfo.win.x/g_mapinfo.win.y < 1)
		g_mapinfo.win.x = g_mapinfo.win.y * 4 / 3;
	g_vars.window.wid = g_mapinfo.win.x;
	g_vars.window.hei = g_mapinfo.win.y;
	g_vars.window.scene = malloc(sizeof(int*) * g_vars.window.hei);
	i = -1;
	while (++i < g_vars.window.hei)
		g_vars.window.scene[i] = malloc(sizeof(int) * g_vars.window.wid);
}

void	init_data(void)
{
	int i;

	init_window();

	g_mlx.mlx = mlx_init();
	g_mlx.win = mlx_new_window(g_mlx.mlx, g_mapinfo.win.x, g_mapinfo.win.y, "new window");
	g_mlx.img = mlx_new_image(g_mlx.mlx,g_mapinfo.win.x,g_mapinfo.win.y);
	g_mlx.data = (int*)mlx_get_data_addr(g_mlx.img,&g_mlx.bpp,&g_mlx.sl,&g_mlx.endian);
	
	g_vars.player.pos = g_mapinfo.pos;

	g_vars.map.size = g_mapinfo.rc;
	g_vars.map.data = g_mapinfo.map;

	init_texture(&g_vars, g_mapinfo.path_list);
	init_sprite(&g_vars.sprite, g_vars.map);

	g_vars.zbuf = malloc(sizeof(double) * g_vars.window.wid);

	i = -1;
	while (++i < 3)
	{
		g_vars.f_rgb[i] = g_mapinfo.fc_rgb[0][i];
		g_vars.c_rgb[i] = g_mapinfo.fc_rgb[1][i];
	}

	i = -1;
	while (g_news[++i] != g_mapinfo.news && i < 5);
	g_vars.player.dir = g_dir[i]; //initial direction vector
	g_vars.player.plane = g_plane[i]; // camera plane

}
