#include "./cub3d.h"

void Rotate(t_pos_doub *vec, t_player *player)
{
	int d;
	double oldx;
	double rad;
	
	d = (player->key == 'R' ? 1 : -1);
	rad = player->rotspeed;
	oldx = vec->x;
	vec->x = vec->x * cos(d * rad) - vec->y * sin(d* rad);
	vec->y = oldx * sin(d * rad) + vec->y * cos (d * rad);
}

void Move(int **map, t_player *player)
{
	int d;
	t_pos_doub delt;

	d = (player->key == 'W' ? 1 : -1);
	delt.x = player->dir.x * player->movespeed;
	delt.y = player->dir.y * player->movespeed;
	if (map[(int)player->pos.y][(int)(player->pos.x + d * delt.x)] != 1)
		player->pos.x += d * delt.x;
	if (map[(int)(player->pos.y + d * delt.y)][(int)player->pos.x] != 1)
		player->pos.y += d * delt.y;	
}

void Move2(int **map, t_player *player)
{
	int d;
	t_pos_doub delt;
	
	d = (player->key == 'D' ? 1 : -1);
	delt.x = player->plane.x/PLANE * player->movespeed;
	delt.y = player->plane.y/PLANE * player->movespeed;
	if (map[(int)player->pos.y][(int)(player->pos.x + d * delt.x)] != 1)
		player->pos.x += d * delt.x;
	if (map[(int)(player->pos.y + d * delt.y)][(int)player->pos.x] != 1)
		player->pos.y += d * delt.y;	
}

void update_player(int **map, t_player *player)
{
	double time;
	double frametime;

	time = clock();
	frametime = (time - player->time) / CLOCKS_PER_SEC;
	player->time = time;
	player->movespeed = frametime * 30;
    player->rotspeed = frametime * 10; 
	if (player->key == 'W' || player->key == 'S') 
		Move(map, player);
	else if (player->key == 'A' || player->key == 'D')
		Move2(map, player);
	else if (player->key == 'R' || player->key == 'L') 
	{
		Rotate(&player->dir, player);
		Rotate(&player->plane, player);
	}
	player->key = 0;
}