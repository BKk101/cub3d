#include "./cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int	keyboard(int keycode, t_vars *vars)
{
	int t, r, g, b;
	
	if (keycode == 8)
	{
		printf("trgb? :");
		scanf("%d %d %d %d", &t,&r,&g,&b);
		vars->color = create_trgb(t,r,g,b);
	}
	else if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == 0)
	{
		printf("a is pressed\n");
	}
	return 0;
}

int key_release(int keycode, void *param)
{
	if (keycode == 0)
	{
		printf("a is released\n");
	}
	return 0;
}

int mouse(int button, int x, int y, t_vars *vars)
{
	printf("%d x:%d y:%d\n", button, x, y);
	return 0;
}

int mouse_move(int x, int y, void *param)
{
	printf("x:%d y:%d\n", x,y);
	return 0;
}

int render_next_frame(t_vars *vars)
{
	int rainbow[7][3] = {{255,000,000}, {255,102,000}, {255,255,000},
{000,255,000},{000,000,255},{000,000,102},{127,000,255}};
	
	vars->elapsed = (double)(clock() -  vars->start) / CLOCKS_PER_SEC;
	int a = (int)(1 * vars->elapsed);
	vars->color = create_trgb(100 * a % 100, rainbow[a%7][0], rainbow[a%7][1], rainbow[a%7][2]);
	for (int i=0;i<500;i++) {
		for (int j=0;j<500;j++) {
			mlx_pixel_put(vars->mlx, vars->win, 0+i, 0+j, vars->color);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 125, 150);
	return 0;
}

int main(int argc, char **argv)
{
	t_vars	vars;
	t_map	map_info;
	t_map2d map_2d;
	int		img_wid = 500;
	int		img_hei = 500;

	vars.color = create_trgb(0,255,100,170);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "new window");
	vars.start = clock();
	vars.img = mlx_xpm_file_to_image(vars.mlx, "./images/pengsu.xpm", &img_wid, &img_hei);
	map_read(&map_info, &map_2d, "./maps/map.cub");
	for (int i=0;i<map_2d.col;i++) {
		for (int j=0;j<map_2d.row;j++)
			printf("%4d", map_2d.arr[i][j]);
		printf("\n");
	}
	//2dmap_draw();
	mlx_hook(vars.win, 2, 0, keyboard, &vars);
	mlx_hook(vars.win, 3, 0, key_release, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
