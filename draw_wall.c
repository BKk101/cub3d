/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:28:53 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 08:30:22 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	calc_wall_info(t_wallinfo *info, t_vars *vars, int x)
{
	int h;

	h = vars->window.hei;
	info->ray = init_ray(vars->player, x, vars->window.wid);
	info->pwall_dist = calc_pwall_dist(vars, &(info->ray));
	info->line_h = info->pwall_dist == 0 ? h : (int)(h / info->pwall_dist);
	info->draw_s = info->line_h > h ? 0 : (h - info->line_h) / 2;
	info->draw_e = info->line_h >= h ? h - 1 : (info->line_h + h) / 2;
	if (info->ray.side)
	{
		info->tex_n = info->ray.dir.y > 0 ? 1 : 0;
		info->wall_x = vars->player.pos.x + info->pwall_dist
		* info->ray.dir.x;
	}
	else
	{
		info->tex_n = info->ray.dir.x > 0 ? 3 : 2;
		info->wall_x = vars->player.pos.y + info->pwall_dist
		* info->ray.dir.y;
	}
	info->wall_x -= floor(info->wall_x);
	vars->zbuf[x] = info->pwall_dist;
}

void	calc_tex_info(t_wallinfo *wallinfo, t_vars *vars)
{
	wallinfo->tex_w = vars->texture[wallinfo->tex_n].size.x;
	wallinfo->tex_h = vars->texture[wallinfo->tex_n].size.y;
	wallinfo->tex_x = (int)(wallinfo->wall_x * (double)wallinfo->tex_w);
	if ((wallinfo->ray.side == 0 && wallinfo->ray.dir.x > 0) ||
		(wallinfo->ray.side == 1 && wallinfo->ray.dir.y < 0))
		wallinfo->tex_x = wallinfo->tex_w - wallinfo->tex_x - 1;
	wallinfo->step = 1.0 * wallinfo->tex_h / wallinfo->line_h;
	wallinfo->tex_pos = (wallinfo->draw_s - vars->window.hei / 2
		+ wallinfo->line_h / 2) * wallinfo->step;
}

int		get_tex_color(t_wallinfo *wallinfo, t_vars *vars)
{
	int tex_y;
	int pos;

	tex_y = (int)wallinfo->tex_pos & (wallinfo->tex_h - 1);
	pos = wallinfo->tex_h * tex_y + wallinfo->tex_x;
	return (vars->texture[wallinfo->tex_n].data[pos]);
}

void	draw_wall(t_vars *vars)
{
	int				x;
	int				y;
	t_wallinfo		wallinfo;

	x = -1;
	while (++x < vars->window.wid)
	{
		calc_wall_info(&wallinfo, vars, x);
		calc_tex_info(&wallinfo, vars);
		y = wallinfo.draw_s - 1;
		while (++y < wallinfo.draw_e)
		{
			vars->window.scene[y][x] = get_tex_color(&wallinfo, vars);
			wallinfo.tex_pos += wallinfo.step;
		}
	}
}
