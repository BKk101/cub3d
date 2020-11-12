/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:02 by bykim             #+#    #+#             */
/*   Updated: 2020/11/13 00:56:07 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_mlx		g_mlx;
t_mapinfo	g_mapinfo;
t_vars		g_vars;

void	redraw(t_mlx mlx)
{
	int i;
	int j;
	int tmp;

	i = -1;
	while (++i < g_vars.window.hei)
	{
		j = -1;
		tmp = i * mlx.sl / 4; //mlx.sl/4 == Width
		while (++j < g_vars.window.wid)
			mlx.data[tmp + j] = g_vars.window.scene[i][j];
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
}

void		update_scene(void)
{
	draw_background(&g_vars.window, g_vars.f_rgb, g_vars.c_rgb);
	draw_wall(&g_vars);
	draw_sprite(&g_vars);
}

int		Loop(t_mlx *mlx)
{
	update_player(g_vars.map.data, &g_vars.player);
	update_scene();
	redraw(*mlx);
	return (0);
}

int main(int argc, char **argv)
{
	Read_mapfile(&g_mapinfo, "./maps/map.cub");
	Init_data();

	mlx_hook(g_mlx.win, 2, 0, Keyboard, &g_vars); //keypressed
	mlx_hook(g_mlx.win, 4, 0, Mouse, &g_vars); //mousepressed
	mlx_hook(g_mlx.win, 17, 0, Exit, 0);
	mlx_loop_hook(g_mlx.mlx, Loop, &g_mlx);
	mlx_loop(g_mlx.mlx);
}
