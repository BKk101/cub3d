#include "./cub3d.h"

void	calc_sprite_info(t_sprinfo *info, t_sprite *sprite)
{
	info->w = g_vars.window.wid;
	info->h = g_vars.window.hei;
	info->sprite_x = sprite->pos.x - g_vars.player.pos.x;
	info->sprite_y = sprite->pos.y - g_vars.player.pos.y;
	info->inv_det = 1.0 / (g_vars.player.plane.x * g_vars.player.dir.y
		- g_vars.player.dir.x * g_vars.player.plane.y);
	info->transform_x = info->inv_det * (g_vars.player.dir.y * info->sprite_x
		- g_vars.player.dir.x * info->sprite_y);
	info->transform_y = info->inv_det * (-g_vars.player.plane.y * info->sprite_x
		+ g_vars.player.plane.x * info->sprite_y);
	info->sprite_screen_x = (int)((info->w / 2)
		* (1 + info->transform_x / info->transform_y));
	info->sprite_h = abs((int)(info->h / (info->transform_y)));
	info->draw_start_y = ft_max(0, -info->sprite_h / 2 + info->h / 2);
	info->draw_end_y = ft_min(info->h - 1, info->sprite_h / 2 + info->h / 2);
	info->sprite_w = abs((int)(info->h / (info->transform_y)));
	info->draw_start_x = ft_max(0, -info->sprite_w / 2 + info->sprite_screen_x);
	info->draw_end_x = ft_min(info->w - 1,
		info->sprite_w / 2 + info->sprite_screen_x);
	info->tex_width = g_vars.texture[4].size.x;
	info->tex_height = g_vars.texture[4].size.y;
}

void	draw_node2(t_sprinfo *info, t_sprite *sprite, int line)
{
	int y;
	int tmp;

	y = info->draw_start_y - 1;
	while (++y < info->draw_end_y)
	{
		info->d = y * 256 - info->h * 128 + info->sprite_h * 128;
		info->tex_y = (info->d * info->tex_height) / info->sprite_h / 256;
		tmp = info->tex_width * info->tex_y + info->tex_x;
		info->color = g_vars.texture[sprite->tex_num].data[tmp];
		if ((info->color & 0x00FFFFFF) != 0)
			g_vars.window.scene[y][line] = info->color;
	}
}

void	draw_node(t_sprite *sprite)
{
	t_sprinfo	info;
	int			line;
	int			tmp; 

	calc_sprite_info(&info, sprite);
	line = info.draw_start_x - 1;
	while (++line < info.draw_end_x)
	{
		tmp = line - (-info.sprite_w / 2 + info.sprite_screen_x);
		info.tex_x = (int)(256 * tmp * info.tex_width / info.sprite_w) / 256;
		if (line > 0 && line < info.w && info.transform_y > 0
			&& info.transform_y < g_vars.zbuf[line])
			draw_node2(&info, sprite, line);
	}
}

int		compare(t_sprite *st1, t_sprite *st2)
{
	int st1_dist;
	int st2_dist;

	st1_dist = pow(st1->pos.x - g_vars.player.pos.x, 2)
				+ pow(st1->pos.y - g_vars.player.pos.y, 2);
	st2_dist = pow(st2->pos.x - g_vars.player.pos.x, 2)
				+ pow(st2->pos.y - g_vars.player.pos.y, 2);
	return (st1_dist < st2_dist);
}

void	draw_sprite(t_vars *vars)
{
	t_list *cur;

	sort_list(vars->sprite, compare);
	cur = vars->sprite;
	while (cur)
	{
		draw_node(cur->content);
		cur = cur->next;
	}
}
