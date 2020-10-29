/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:02 by bykim             #+#    #+#             */
/*   Updated: 2020/10/30 01:04:45 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#define TILE_SIZE 15

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int	keyboard(int keycode, t_vars *vars)
{
	int t, r, g, b;
	
	mlx_clear_window(vars->mlx, vars->win);
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
	else if (keycode == 126)
    {
      printf("up is pressed  %lf\n", vars->ray_info.frameTime);
	  if(vars->map_info.map[(int)(vars->map_info.pos.y)][(int)(vars->map_info.pos.x + vars->ray_info.dir.x * vars->ray_info.moveSpeed)] == 0) vars->map_info.pos.x += vars->ray_info.dir.x * vars->ray_info.moveSpeed;
      if(vars->map_info.map[(int)(vars->map_info.pos.y + vars->ray_info.dir.y * vars->ray_info.moveSpeed)][(int)(vars->map_info.pos.x)] == 0) vars->map_info.pos.y += vars->ray_info.dir.y * vars->ray_info.moveSpeed;
    }
    //move backwards if no wall behind you
    else if (keycode == 125)
    {
      printf("down is pressed  %lf\n", vars->ray_info.frameTime);
	  if(vars->map_info.map[(int)(vars->map_info.pos.y)][(int)(vars->map_info.pos.x - vars->ray_info.dir.x * vars->ray_info.moveSpeed)] == 0) vars->map_info.pos.x -= vars->ray_info.dir.x * vars->ray_info.moveSpeed;
      if(vars->map_info.map[(int)(vars->map_info.pos.y - vars->ray_info.dir.y * vars->ray_info.moveSpeed)][(int)(vars->map_info.pos.x)] == 0) vars->map_info.pos.y -= vars->ray_info.dir.y * vars->ray_info.moveSpeed;
    }
    //rotate to the right
    else if (keycode == 124)
    {
      //both camera direction and camera plane must be rotated
      printf("right is pressed  %lf\n", vars->ray_info.frameTime);
	  double oldDirX = vars->ray_info.dir.x;
      vars->ray_info.dir.x = vars->ray_info.dir.x * cos(-vars->ray_info.rotSpeed) - vars->ray_info.dir.y * sin(-vars->ray_info.rotSpeed);
      vars->ray_info.dir.y = oldDirX * sin(-vars->ray_info.rotSpeed) + vars->ray_info.dir.y * cos(-vars->ray_info.rotSpeed);
      double oldPlaneX = vars->ray_info.plane.x;
      vars->ray_info.plane.x = vars->ray_info.plane.x * cos(-vars->ray_info.rotSpeed) - vars->ray_info.plane.y * sin(-vars->ray_info.rotSpeed);
      vars->ray_info.plane.y = oldPlaneX * sin(-vars->ray_info.rotSpeed) + vars->ray_info.plane.y * cos(-vars->ray_info.rotSpeed);
    }
    //rotate to the left
    else if (keycode == 123)
    {
      //both camera direction and camera plane must be rotated
      printf("left is pressed  %lf\n", vars->ray_info.frameTime);
	  double oldDirX = vars->ray_info.dir.x;
      vars->ray_info.dir.x = vars->ray_info.dir.x * cos(vars->ray_info.rotSpeed) - vars->ray_info.dir.y * sin(vars->ray_info.rotSpeed);
      vars->ray_info.dir.y = oldDirX * sin(vars->ray_info.rotSpeed) + vars->ray_info.dir.y * cos(vars->ray_info.rotSpeed);
      double oldPlaneX = vars->ray_info.plane.x;
      vars->ray_info.plane.x = vars->ray_info.plane.x * cos(vars->ray_info.rotSpeed) - vars->ray_info.plane.y * sin(vars->ray_info.rotSpeed);
      vars->ray_info.plane.y = oldPlaneX * sin(vars->ray_info.rotSpeed) + vars->ray_info.plane.y * cos(vars->ray_info.rotSpeed);
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

int render_next_frame(t_vars *vars)
{
	int rainbow[7][3] = {{255,000,000}, {255,102,000}, {255,255,000},
{000,255,000},{000,000,255},{000,000,102},{127,000,255}};

	vars->elp_time = (double)(clock() -  vars->str_time) / CLOCKS_PER_SEC;
	int a = (int)(100 * vars->elp_time);
	vars->color = create_trgb(100 * a % 100, rainbow[a%7][0], rainbow[a%7][1], rainbow[a%7][2]);
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img_pic.img, 125, 125); //img
	//draw_rectangles(vars);
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img_map.img, 0, 380); //map
	raycast(vars);
	return 0;
}

int main(int argc, char **argv)
{
	t_vars vars;
	int wid = 100;
	int hei = 100;

	read_mapfile(&vars.map_info, "./maps/map.cub");
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map_info.win.x, vars.map_info.win.y + 200, "new window");
	vars.str_time = clock();
	vars.img_pic.img = mlx_xpm_file_to_image(vars.mlx, "./images/rilakkuma.xpm", &wid, &hei);
	//map_validtest();
	vars.img_map.img = mlx_new_image(vars.mlx, vars.map_info.rc.x * TILE_SIZE, vars.map_info.rc.y * TILE_SIZE);
	vars.img_map.data = (int *)mlx_get_data_addr(vars.img_map.img, &vars.img_map.bpp,
&vars.img_map.size_l, &vars.img_map.endian);

	vars.ray_info.dir.x = -1;
	vars.ray_info.dir.y = 0; //initial direction vector
	vars.ray_info.plane.x = 0;
	vars.ray_info.plane.y = 0.66; //the 2d raycaster version of camera plane
	vars.ray_info.time = 0; //time of current frame
	vars.ray_info.oldTime = 0; //time of previous frame

	mlx_hook(vars.win, 2, 0, keyboard, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
