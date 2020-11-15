#include "./cub3d.h"

void	dda(t_ray *ray, char **map, t_pos_doub side_dist, t_pos_int step)
{
	t_pos_doub	delta_dist;

	delta_dist = calc_delta_dist(*ray);
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			ray->map.x += step.x;
			ray->side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			ray->map.y += step.y;
			ray->side = 1;
		}
		if (map[ray->map.y][ray->map.x] == '1')
			break ;
	}
}

double	calc_pwall_dist(t_vars *vars, t_ray *ray)
{
	t_pos_doub	side_dist;
	t_pos_int	step;

	side_dist = calc_side_dist(*ray, vars->player.pos);
	step = calc_step(*ray);
	dda(ray, vars->map.data, side_dist, step);
	if (ray->side == 0)
		return ((ray->map.x - vars->player.pos.x + (1 - step.x) / 2)
			/ ray->dir.x);
	else
		return ((ray->map.y - vars->player.pos.y + (1 - step.y) / 2)
			/ ray->dir.y);
}

t_ray	init_ray(t_player player, int x, int w)
{
	t_ray	ray;
	double	camera_x;

	camera_x = 2 * x / (double)w - 1;
	ray.dir.x = player.dir.x + player.plane.x * camera_x;
	ray.dir.y = player.dir.y + player.plane.y * camera_x;
	ray.map.x = (int)player.pos.x;
	ray.map.y = (int)player.pos.y;
	return (ray);
}
