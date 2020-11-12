/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:02 by bykim             #+#    #+#             */
/*   Updated: 2020/11/13 02:18:47 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_mlx		g_mlx;
t_mapinfo	g_mapinfo;
t_vars		g_vars;

int		Loop(t_mlx *mlx)
{
	update_player(g_vars.map.data, &g_vars.player);
	update_scene();
	redraw(*mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc > 3 || argc == 1
		|| (argc == 3 && ft_strncmp("--save", argv[2], 6) != 0))
		return (Error("invalid argument"));
	Read_mapfile(&g_mapinfo, argv[1]);
	if (argc == 3)
	{
		update_scene();
		//save_bmp();
	}
	else
	{
		init_data();
		mlx_hook(g_mlx.win, 2, 0, Keyboard, &g_vars);
		mlx_hook(g_mlx.win, 4, 0, Mouse, &g_vars);
		mlx_hook(g_mlx.win, 17, 0, Exit, 0);
		mlx_loop_hook(g_mlx.mlx, Loop, &g_mlx);
		mlx_loop(g_mlx.mlx);
	}
}
