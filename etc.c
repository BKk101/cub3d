#if 0
#include "./cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	draw_rectangle(t_vars *vars, int x, int y)
{
	int i;
	int j;
	int color;

	if (vars->map_info.map[y][x] == 1)
		color = vars->color;
	else if (vars->map_info.map[y][x] == 2)
		color = 0x00FF00;
	else if (vars->map_info.map[y][x] == -16)
		color = 0xA9A9A9;
	else
		color = 0xFF0000;
	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			vars->img_map.data[(y  + i) * vars->map_info.rc.x * TILE_SIZE + x + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	while (i < vars->map_info.rc.y)
	{
		j = 0;
		while (j < vars->map_info.rc.x)
		{
			if (vars->map_info.map[i][j] != 0)
				draw_rectangle(vars, j, i);
			j++;
		}
		i++;
	}
}

#endif