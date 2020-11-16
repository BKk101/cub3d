/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:29:14 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 08:21:26 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	update_player(char **map, t_player *player)
{
	double time;
	double frametime;

	time = clock();
	frametime = (time - player->time) / CLOCKS_PER_SEC;
	player->time = time;
	player->movespeed = frametime * 7;
	player->rotspeed = frametime * 3;
	if (player->key == 'W' || player->key == 'S')
		move(map, player);
	else if (player->key == 'A' || player->key == 'D')
		move2(map, player);
	else if (player->key == 'R' || player->key == 'L')
	{
		rotate(&player->dir, player);
		rotate(&player->plane, player);
	}
}

void	update_scene(void)
{
	draw_background(&g_vars.window, g_vars.f_rgb, g_vars.c_rgb);
	draw_wall(&g_vars);
	draw_sprite(&g_vars);
}

void	redraw(t_mlx mlx)
{
	int i;
	int j;
	int tmp;

	i = -1;
	while (++i < g_vars.window.hei)
	{
		j = -1;
		tmp = i * mlx.sl / 4;
		while (++j < g_vars.window.wid)
			mlx.data[tmp + j] = g_vars.window.scene[i][j];
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
}
