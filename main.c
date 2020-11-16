/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:02 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 11:11:07 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_mlx		g_mlx;
t_mapinfo	g_mapinfo;
t_vars		g_vars;

int	loop(t_mlx *mlx)
{
	update_player(g_vars.map.data, &g_vars.player);
	update_scene();
	redraw(*mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc > 3 || argc == 1
		|| (argc == 3 && ft_strncmp("--save", argv[2], 6) != 0))
		return (print_error("invalid argument"));
	if (read_mapfile(&g_mapinfo, argv[1]) == -1)
		return (-1);
	if (!init_data())
		return (-1);
	if (argc == 3)
	{
		update_scene();
		save_bmp(g_vars.window);
	}
	else
	{
		mlx_hook(g_mlx.win, 2, 0, key_press, &g_vars);
		mlx_hook(g_mlx.win, 3, 0, key_release, &g_vars);
		mlx_hook(g_mlx.win, 4, 0, mouse, &g_vars);
		mlx_hook(g_mlx.win, 17, 0, exit_prog, 0);
		mlx_loop_hook(g_mlx.mlx, loop, &g_mlx);
		mlx_loop(g_mlx.mlx);
	}
}
