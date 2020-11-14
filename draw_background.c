#include "./cub3d.h"

void	draw_background(t_window *window, int *floor, int *ceil)
{
	int i;
	int j;

	i = -1;
	while (++i < window->wid)
	{
		j = -1;
		while (++j < window->hei / 2)
			window->scene[j][i] = (ceil[0] << 16) + (ceil[1] << 8) + ceil[2];
		while (j < window->hei)
			window->scene[j++][i] = (floor[0] << 16) + (floor[1] << 8)
				+ floor[2];
	}
}
