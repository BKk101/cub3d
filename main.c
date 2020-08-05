/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:02 by bykim             #+#    #+#             */
/*   Updated: 2020/08/05 19:14:59 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#define TILE_SIZE 16

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

int mouse(int button, int x, int y, t_vars *vars)
{
	printf("%d x:%d y:%d\n", button, x, y);
	return 0;
}

void	draw_rectangle(t_vars *vars, int x, int y)
{
	int i;
	int j;
	int color;

	if (vars->map_info.arr[y][x] == 1)
		color = 0xFFFFFF;
	else if (vars->map_info.arr[y][x] == 2)
		color = 0x00FF00;
	else if (vars->map_info.arr[y][x] == -16)
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
			vars->img_map.data[(y  + i) * vars->map_info.col * TILE_SIZE + x + j] = color;
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
	while (i < vars->map_info.row)
	{
		j = 0;
		while (j < vars->map_info.col)
		{
			if (vars->map_info.arr[i][j] != 0)
				draw_rectangle(vars, j, i);
			j++;
		}
		i++;
	}
}
int render_next_frame(t_vars *vars)
{
	int rainbow[7][3] = {{255,000,000}, {255,102,000}, {255,255,000},
{000,255,000},{000,000,255},{000,000,102},{127,000,255}};

	//vars->elp_time = (double)(clock() -  vars->str_time) / CLOCKS_PER_SEC;
	//int a = (int)(1 * vars->elp_time);
	//vars->color = create_trgb(100 * a % 100, rainbow[a%7][0], rainbow[a%7][1], rainbow[a%7][2]);
	//for (int i=0;i<500;i++) {
	//	for (int j=0;j<500;j++) {
	//		mlx_pixel_put(vars->mlx, vars->win, 0+i, 0+j, vars->color);
	//	}
	//}
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img_pic.img, 125, 125);
	draw_rectangles(vars);
	//draw_lines(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_map.img, 0, 0);
	return 0;
}

int main(int argc, char **argv)
{
	t_vars	vars;
	int wid = 100;
	int hei = 100;

	read_mapfile(&vars.map_info, "./maps/map.cub");
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map_info.win_wid, vars.map_info.win_hei, "new window");
	vars.str_time = clock();
	vars.img_pic.img = mlx_xpm_file_to_image(vars.mlx, "./images/pengsu.xpm", &wid, &hei);
	//map_validtest();
	//2dmap_draw();
	vars.img_map.img = mlx_new_image(vars.mlx, vars.map_info.col * TILE_SIZE, vars.map_info.row * TILE_SIZE);
	vars.img_map.data = (int *)mlx_get_data_addr(vars.img_map.img, &vars.img_map.bpp,
&vars.img_map.size_l, &vars.img_map.endian);
	
	mlx_hook(vars.win, 2, 0, keyboard, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
