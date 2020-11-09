#include "./cub3d.h"

t_pos_doub	g_dir[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
t_pos_doub	g_plane[4] = {{PLANE, 0}, {-PLANE, 0}, {0, -PLANE} ,{0, PLANE}};
static char	g_news[4] = "NSWE";

void Init_data(void)
{
	int i;

	g_mlx.mlx = mlx_init();
	g_mlx.win = mlx_new_window(g_mlx.mlx, g_mapinfo.win.x, g_mapinfo.win.y, "new window");
	g_mlx.img = mlx_new_image(g_mlx.mlx,g_mapinfo.win.x,g_mapinfo.win.y);
	g_mlx.data = (int*)mlx_get_data_addr(g_mlx.img,&g_mlx.bpp,&g_mlx.sl,&g_mlx.endian);

	g_vars.window.wid = g_mapinfo.win.x;
	g_vars.window.hei = g_mapinfo.win.y;
	g_vars.window.scene = malloc(sizeof(int*) * g_mapinfo.win.y);
	i = -1;
	while (++i < g_mapinfo.win.y)
		g_vars.window.scene[i] = malloc(sizeof(int) * g_mapinfo.win.x);
	
	g_vars.player.pos = g_mapinfo.pos;

	g_vars.map.size = g_mapinfo.rc;
	g_vars.map.data = g_mapinfo.map;

	parse_key_texture(&g_vars, g_mapinfo.path_list);

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
