/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:29:01 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 08:25:28 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_pos_doub	g_dir[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
t_pos_doub	g_plane[4] = {{PLANE, 0}, {-PLANE, 0}, {0, -PLANE}, {0, PLANE}};
static char	g_news[4] = "NSWE";

void	init_sprite(void)
{
	int			i;
	int			j;
	t_sprite	*p;

	i = -1;
	while (++i < g_vars.map.size.y)
	{
		j = -1;
		while (++j < g_vars.map.size.x)
			if (g_vars.map.data[i][j] == '2')
			{
				p = malloc(sizeof(t_sprite));
				p->pos.x = 0.5 + j;
				p->pos.y = 0.5 + i;
				p->tex_num = 4;
				ft_lstadd_back(&g_vars.sprite, ft_lstnew((void*)p));
			}
	}
}

int		init_texture(void)
{
	int		i;
	int		tmp;
	void	*img;

	i = -1;
	while (++i < 5)
	{
		img = mlx_xpm_file_to_image(g_mlx.mlx, g_mapinfo.path_list[i],
			&g_vars.texture[i].size.x, &g_vars.texture[i].size.y);
		if (!img)
			break ;
		g_vars.texture[i].data = (int *)mlx_get_data_addr(img, &tmp,
			&tmp, &tmp);
	}
	if (!img)
		print_error("invalid_texture_file");
	return (img != 0);
}

void	init_mlx(void)
{
	g_mapinfo.win.x = ft_min(g_mapinfo.win.x, 1920);
	g_mapinfo.win.x = ft_max(g_mapinfo.win.x, 400);
	g_mapinfo.win.y = ft_min(g_mapinfo.win.y, 1080);
	g_mapinfo.win.y = ft_max(g_mapinfo.win.y, 300);
	if ((double)g_mapinfo.win.x / g_mapinfo.win.y > 2.5)
		g_mapinfo.win.x = g_mapinfo.win.y * 4 / 3;
	if ((double)g_mapinfo.win.x / g_mapinfo.win.y < 0.7)
		g_mapinfo.win.x = g_mapinfo.win.y * 4 / 3;
	g_mlx.mlx = mlx_init();
	g_mlx.win = mlx_new_window(g_mlx.mlx, g_mapinfo.win.x,
		g_mapinfo.win.y, "new window");
	g_mlx.img = mlx_new_image(g_mlx.mlx, g_mapinfo.win.x,
		g_mapinfo.win.y);
	g_mlx.data = (int*)mlx_get_data_addr(g_mlx.img, &g_mlx.bpp,
		&g_mlx.sl, &g_mlx.endian);
}

void	init_window(void)
{
	int i;

	g_vars.window.wid = g_mapinfo.win.x;
	g_vars.window.hei = g_mapinfo.win.y;
	g_vars.window.scene = malloc(sizeof(int*) * g_vars.window.hei);
	i = -1;
	while (++i < g_vars.window.hei)
		g_vars.window.scene[i] = malloc(sizeof(int) * g_vars.window.wid);
}

int		init_data(void)
{
	int i;

	init_mlx();
	init_window();
	init_mapdata(&g_mapinfo);
	g_vars.map.size = g_mapinfo.rc;
	g_vars.map.data = g_mapinfo.map;
	if (init_texture() == 0)
		return (0);
	init_sprite();
	g_vars.zbuf = malloc(sizeof(double) * g_vars.window.wid);
	i = -1;
	while (++i < 3)
	{
		g_vars.f_rgb[i] = g_mapinfo.fc_rgb[0][i];
		g_vars.c_rgb[i] = g_mapinfo.fc_rgb[1][i];
	}
	i = 0;
	while (g_news[i] != g_mapinfo.news && i < 5)
		i++;
	g_vars.player.dir = g_dir[i];
	g_vars.player.plane = g_plane[i];
	g_vars.player.pos = g_mapinfo.pos;
	return (1);
}
