/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:29:28 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 08:21:09 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	rotate(t_pos_doub *vec, t_player *player)
{
	int		d;
	double	oldx;
	double	rad;

	d = (player->key == 'R' ? 1 : -1);
	rad = player->rotspeed;
	oldx = vec->x;
	vec->x = vec->x * cos(d * rad) - vec->y * sin(d * rad);
	vec->y = oldx * sin(d * rad) + vec->y * cos(d * rad);
}

void	move(char **map, t_player *player)
{
	int			d;
	t_pos_doub	delt;

	d = (player->key == 'W' ? 1 : -1);
	delt.x = player->dir.x * player->movespeed;
	delt.y = player->dir.y * player->movespeed;
	if (map[(int)player->pos.y][(int)(player->pos.x + d * delt.x)] != '1')
		player->pos.x += d * delt.x;
	if (map[(int)(player->pos.y + d * delt.y)][(int)player->pos.x] != '1')
		player->pos.y += d * delt.y;
}

void	move2(char **map, t_player *player)
{
	int			d;
	t_pos_doub	delt;

	d = (player->key == 'D' ? 1 : -1);
	delt.x = (player->plane.x / PLANE) * player->movespeed;
	delt.y = (player->plane.y / PLANE) * player->movespeed;
	if (map[(int)player->pos.y][(int)(player->pos.x + d * delt.x)] != '1')
		player->pos.x += d * delt.x;
	if (map[(int)(player->pos.y + d * delt.y)][(int)player->pos.x] != '1')
		player->pos.y += d * delt.y;
}
