/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:02 by bykim             #+#    #+#             */
/*   Updated: 2020/11/03 23:36:14 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_mlx		g_mlx;
t_mapinfo	g_mapinfo;
t_rayinfo	g_rayinfo;
t_vars		g_vars;
t_pos_doub	g_dir[4] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}};
t_pos_doub	g_plane[4] = {{PLANE, 0}, {0, PLANE}, {0, -PLANE}, {-PLANE, 0}};
static char	g_news[4] = "NEWS";

//int Render_next_frame(t_vars *vars)
//{
//	mlx_clear_window(vars->mlx->mlx, vars->mlx->win);
//	Raycast(vars);
//	return 0;
//}


void	redraw(t_mlx mlx)
{
	int i;
	int j;
	int tmp;

	i = -1;
	while (++i < g_mapinfo.win.y)
	{
		j = -1;
		tmp = i * g_mapinfo.win.x; //mlx.sl / 4;
		while (++j < g_mapinfo.win.x)
			mlx.data[tmp + j] = g_cub.window.scene[i][j];
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
}

void		update_scene(void)
{
	draw_background(&g_cub.window, g_cub.floor, g_cub.ceil);
	draw_wall(&g_cub);
	draw_sprite(&g_cub);
}

int		Loop(t_vars *vars)
{
	//calc_movement(&g_cub.player, &g_cub.control);
	//update_player(g_cub.map.data, &g_cub.player);
	update_scene();
	redraw(*(vars->mlx));
	return (0);
}

int main(int argc, char **argv)
{
	
	g_vars.mlx = &g_mlx;
	g_vars.m_info = &g_mapinfo;
	g_vars.r_info = &g_rayinfo;
	
	Read_mapfile(&g_mapinfo, "./maps/map.cub");
	g_mlx.mlx = mlx_init();
	g_mlx.win = mlx_new_window(g_mlx.mlx, g_mapinfo.win.x, g_mapinfo.win.y, "new window");
	g_mlx.img = mlx_new_image(g_mlx.mlx,g_mapinfo.win.x,g_mapinfo.win.y);
	g_mlx.data = (int *)mlx_get_data_addr(g_mlx.img,&g_mlx.bpp,&g_mlx.sl,&g_mlx.endian);
	//g_mlx.data[i*width + j] = color;
	
	int news = -1;
	while (g_news[++news] != g_mapinfo.news && news < 5);
	g_rayinfo.dir = g_dir[news]; //initial direction vector
	g_rayinfo.plane = g_plane[news]; // camera plane

	mlx_hook(g_mlx.win, 2, 0, Keyboard, &g_vars); //keypressed
	mlx_hook(g_mlx.win, 4, 0, Mouse, &g_vars); //mousepressed
	mlx_loop_hook(g_mlx.mlx, Loop, &g_vars);
	mlx_loop(g_mlx.mlx);
}
