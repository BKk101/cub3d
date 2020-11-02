/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:02 by bykim             #+#    #+#             */
/*   Updated: 2020/11/03 01:47:52 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_mlx		g_mlx;
t_mapinfo	g_mapinfo;
t_rayinfo	g_rayinfo;
t_vars		g_vars;
t_pos_doub	g_dir[4] = {{0,-1},{1,0},{-1,0},{0,1}};
t_pos_doub	g_plane[4] = {{PLANE,0},{0,PLANE},{0,-PLANE},{-PLANE,0}};
static char	g_news[4] = "NEWS";

int Render_next_frame(t_vars *vars)
{
	mlx_clear_window(vars->mlx->mlx, vars->mlx->win);
	Raycast(vars);
	return 0;
}

int main(int argc, char **argv)
{
	
	g_vars.mlx = &g_mlx;
	g_vars.m_info = &g_mapinfo;
	g_vars.r_info = &g_rayinfo;
	
	Read_mapfile(&g_mapinfo, "./maps/map.cub");
	g_mlx.mlx = mlx_init();
	g_mlx.win = mlx_new_window(g_mlx.mlx, g_mapinfo.win.x, g_mapinfo.win.y, "new window");
	
	int news = -1;
	while (g_news[++news] != g_mapinfo.news && news < 5);
	g_rayinfo.dir = g_dir[news]; //initial direction vector
	g_rayinfo.plane = g_plane[news]; // camera plane

	mlx_hook(g_mlx.win, 2, 0, Keyboard, &g_vars); //keypressed
	mlx_hook(g_mlx.win, 4, 0, Mouse, &g_vars); //mousepressed
	mlx_loop_hook(g_mlx.mlx, Render_next_frame, &g_vars);
	mlx_loop(g_mlx.mlx);
}
