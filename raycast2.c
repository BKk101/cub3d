#include "./cub3d.h"

t_pos_doub	calc_delta_dist(t_ray ray)
{
	t_pos_doub delta_dist;

	delta_dist.x = fabs(1 / ray.dir.x);
	delta_dist.y = fabs(1 / ray.dir.y);
	return (delta_dist);
}

t_pos_int	calc_step(t_ray ray)
{
	t_pos_int step;

	if (ray.dir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray.dir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

t_pos_doub	calc_side_dist(t_ray ray, t_pos_doub pos)
{
	t_pos_doub	side_dist;
	t_pos_doub	delta_dist;

	delta_dist = calc_delta_dist(ray);
	if (ray.dir.x < 0)
		side_dist.x = (pos.x - ray.map.x) * delta_dist.x;
	else
		side_dist.x = (ray.map.x + 1.0 - pos.x) * delta_dist.x;
	if (ray.dir.y < 0)
		side_dist.y = (pos.y - ray.map.y) * delta_dist.y;
	else
		side_dist.y = (ray.map.y + 1.0 - pos.y) * delta_dist.y;
	return (side_dist);
}
