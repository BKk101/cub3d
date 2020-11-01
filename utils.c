#include "./cub3d.h"

void	free_dptr(char **start, int len)
{
	int i;

	i = -1;
	while (++i <= len)
		free(*(start + i));
}

void Rotate(t_pos_doub *s, char dir)
{
	int d;
	double oldx;
	double rad;
	
	d = (dir == 'R' ? 1 : -1);
	rad = g_rayinfo.rotSpeed;
	oldx = s->x;
	s->x = s->x * cos(d * rad) - s->y * sin(d* rad);
	s->y = oldx * sin(d * rad) + s->y * cos (d * rad);
}

void Move(t_pos_doub *pos, char dir)
{
	int d;
	double deltx;
	double delty;

	d = (dir == 'U' ? 1 : -1);
	deltx = g_rayinfo.dir.x * g_rayinfo.moveSpeed;
	delty = g_rayinfo.dir.y * g_rayinfo.moveSpeed;
	if (g_mapinfo.map[(int)pos->y][(int)(pos->x + d * deltx)] == 0)
		pos->x += d* deltx;
	if (g_mapinfo.map[(int)(pos->y + d * delty)][(int)pos->x] == 0)
		pos->y += d* delty;	
}