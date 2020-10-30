/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:02 by bykim             #+#    #+#             */
/*   Updated: 2020/10/30 16:39:38 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_mlx		g_mlx;
t_mapinfo	g_mapinfo;
t_rayinfo	g_rayinfo;
t_vars		g_vars;

int render_next_frame(t_vars *vars)
{
	//draw_rectangles(mlx);
	//mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 380); //map
	raycast(vars);
	return 0;
}

int main(int argc, char **argv)
{
	
	g_vars.mlx = &g_mlx;
	g_vars.m_info = &g_mapinfo;
	g_vars.r_info = &g_rayinfo;
	
	read_mapfile(&g_mapinfo, "./maps/map.cub");
	g_mlx.mlx = mlx_init();
	g_mlx.win = mlx_new_window(g_mlx.mlx, g_mapinfo.win.x, g_mapinfo.win.y, "new window");
	//g_mlx.str_time = clock();
	g_mlx.img = mlx_new_image(g_mlx.mlx, g_mapinfo.rc.x * TILE_SIZE, g_mapinfo.rc.y * TILE_SIZE);
	g_mlx.data = (int *)mlx_get_data_addr(g_mlx.img, &g_mlx.bpp,&g_mlx.sl, &g_mlx.endian);

	g_rayinfo.dir.x = -1;
	g_rayinfo.dir.y = 0; //initial direction vector
	g_rayinfo.plane.x = 0;
	g_rayinfo.plane.y = 0.66; //the 2d raycaster version of camera plane
	g_rayinfo.time = 0; //time of current frame
	g_rayinfo.oldTime = 0; //time of previous frame

	mlx_hook(g_mlx.win, 2, 0, keyboard, &g_vars); //keypressed
	mlx_hook(g_mlx.win, 4, 0, mouse, &g_vars); //mousepressed
	mlx_loop_hook(g_mlx.mlx, render_next_frame, &g_vars);
	mlx_loop(g_mlx.mlx);
}
