#include "./cub3d.h"

void	calc_draw_info(t_wallinfo *info, t_vars *vars, int x)
{
	int h;

	h = vars->window.hei;
	info->ray = init_ray(vars->player, x, vars->window.wid);
	info->perp_wall_dist = calc_perp_wall_dist(vars, &(info->ray));
	info->line_h = info->perp_wall_dist == 0 ? h : (int)(h / info->perp_wall_dist);
	info->draw_s = info->line_h > h ? 0 : (h - info->line_h) / 2;
	info->draw_e = info->line_h >= h ? h - 1 : (info->line_h + h) / 2;
	if (info->ray.side)
	{
		info->tex_n = info->ray.dir.y > 0 ? 0 : 1;
		info->wall_x = vars->player.pos.x + info->perp_wall_dist
		* info->ray.dir.x;
	}
	else
	{
		info->tex_n = info->ray.dir.x > 0 ? 2 : 3;
		info->wall_x = vars->player.pos.y + info->perp_wall_dist
		* info->ray.dir.y;
	}
	info->wall_x -= floor(info->wall_x);
	vars->zbuf[x] = info->perp_wall_dist;
}

void	calc_draw_tex_info(t_wallinfo *wallinfo, t_vars *vars)
{
	wallinfo->tex_w = vars->texture[wallinfo->tex_n].size.x;
	wallinfo->tex_h = vars->texture[wallinfo->tex_n].size.y;
	wallinfo->tex_x = (int)(wallinfo->wall_x * (double)wallinfo->tex_w);
	if ((wallinfo->ray.side == 0 && wallinfo->ray.dir.x > 0) || (wallinfo->ray.side == 1 && wallinfo->ray.dir.y < 0))
		wallinfo->tex_x = wallinfo->tex_w - wallinfo->tex_x - 1;
	wallinfo->step = 1.0 * wallinfo->tex_h / wallinfo->line_h;
	wallinfo->tex_pos = (wallinfo->draw_s - vars->window.hei / 2 + wallinfo->line_h / 2) * wallinfo->step;
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
		calc_draw_info(&wallinfo, vars, x);
		calc_draw_tex_info(&wallinfo, vars);
		y = wallinfo.draw_s - 1;
		while (++y < wallinfo.draw_e)
		{
			vars->window.scene[y][x] = get_tex_color(&wallinfo, vars);
			wallinfo.tex_pos += wallinfo.step;
		}
	}
}

void	draw_background(t_window *window, int *floor, int *ceil)
{
	int i;
	int j;

	i = -1;
	while (++i < window->wid)
	{
		j = -1;
		while (++j < window->hei / 2) //??
			window->scene[j][i] = (ceil[0] << 16) + (ceil[1] << 8) + ceil[2];
		while (j < window->hei)
			window->scene[j++][i] = (floor[0] << 16) + (floor[1] << 8) + floor[2];
	}
}
