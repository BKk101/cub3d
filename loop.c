#include "./cub3d.h"

void	update_player(int **map, t_player *player)
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

void	update_scene(void)
{
	draw_background(&g_vars.window, g_vars.f_rgb, g_vars.c_rgb);
	draw_wall(&g_vars);
	draw_sprite(&g_vars);
}

void	redraw(t_mlx mlx)
{
	int i;
	int j;
	int tmp;

	i = -1;
	while (++i < g_vars.window.hei)
	{
		j = -1;
		tmp = i * mlx.sl / 4; //mlx.sl/4 == Width
		while (++j < g_vars.window.wid)
			mlx.data[tmp + j] = g_vars.window.scene[i][j];
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
}