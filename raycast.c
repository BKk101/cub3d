#include "./cub3d.h"

static int g_color[4] = {0xff0000,0x00ff00,0x0000ff,0xffff00};

int		Raycast(t_vars *vars)
{
	t_pos_int i;
	t_pos_int screen;
	t_pos_int map;
	t_pos_int step;
	t_pos_doub ray;
	t_pos_doub sideDist;
	t_pos_doub deltDist;
	int side;
	int height;
	int sp;
	int ep;
	double time;
	double cam;
	double pWallDist;
	
	screen = vars->m_info->win;
	time  = (double)clock();
	
	for(i.x = 0; i.x < screen.x; i.x++)
    {
		cam = 2 * i.x / (double)screen.x - 1; //x-coordinate in camera space
		ray.x = vars->r_info->dir.x + vars->r_info->plane.x * cam;
		ray.y = vars->r_info->dir.y + vars->r_info->plane.y * cam;
		
		map.x = (int)vars->m_info->pos.x;
		map.y = (int)vars->m_info->pos.y;
		
		//calculate step and initial sideDist
		deltDist.x = Calc_step_sidedist(ray.x, vars->m_info->pos.x, &step.x, &sideDist.x);
		deltDist.y = Calc_step_sidedist(ray.y, vars->m_info->pos.y, &step.y, &sideDist.y);
    	
		//perform DDA
		side = DDA(&sideDist, &map, deltDist, step, ray);
		
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    	if (side == 1 || side == 2) 
			pWallDist = (map.x - vars->m_info->pos.x + (1 - step.x) / 2) / ray.x;
		else
			pWallDist = (map.y - vars->m_info->pos.y + (1 - step.y) / 2) / ray.y;

		//Calculate height of line to draw on screen
      	height = pWallDist == 0 ? (int)screen.y : (int)(screen.y / pWallDist);

      	//calculate lowest and highest pixel to fill in current stripe
      	sp = (-height / 2 + screen.y / 2) < 0 ? 0 : (-height / 2 + screen.y / 2);
      	ep = (height / 2 + screen.y / 2) >= screen.y ? screen.y - 1 : (height / 2 + screen.y / 2);

		for (i.y=screen.y-1;i.y>ep;i.y--)
			mlx_pixel_put(vars->mlx->mlx, vars->mlx->win, i.x, i.y, 0xffffff); //floor
		for (i.y=sp;i.y<=ep;i.y++)
			mlx_pixel_put(vars->mlx->mlx, vars->mlx->win, i.x, i.y, g_color[side]);
		for (i.y=0;i.y<sp;i.y++)
			mlx_pixel_put(vars->mlx->mlx, vars->mlx->win, i.x, i.y, 0x666666); //ceiling
	}
    vars->r_info->frameTime = ((double)clock()- time) / CLOCKS_PER_SEC; //frameTime is the time this frame has taken, in seconds
	vars->r_info->moveSpeed = vars->r_info->frameTime * 30; //the constant value is in squares/second
    vars->r_info->rotSpeed = vars->r_info->frameTime * 10; //the constant value is in radians/second

	if (vars->r_info->key == 'W' || vars->r_info->key == 'S') 
		Move(&vars->m_info->pos, vars->r_info->key);
	else if (vars->r_info->key == 'A' || vars->r_info->key == 'D')
		Move2(&vars->m_info->pos, vars->r_info->key);
	else if (vars->r_info->key == 'R' || vars->r_info->key == 'L') 
	{
		Rotate(&vars->r_info->dir, vars->r_info->key);
		Rotate(&vars->r_info->plane, vars->r_info->key);
	}
	vars->r_info->key = 0;	return 0;
}

double Calc_step_sidedist(double ray, double pos, int *step, double *sideDist)
{
	double deltDist;
	
	deltDist = fabs(1 / ray);
	if (ray < 0)
    {
      	*step = -1;
      	*sideDist = (pos - (int)pos) * deltDist;
    }
    else
    {
      	*step = 1;
      	*sideDist = ((int)pos + 1 - pos) * deltDist;
    }
	return deltDist;
}

int DDA(t_pos_doub *sideDist, t_pos_int *map, t_pos_doub deltDist, t_pos_int step, t_pos_doub ray)
{
	int hit;
	int side;

	hit = 0;
	while (hit == 0)
    {
    	if (sideDist->x < sideDist->y)
    	{
    	  sideDist->x += deltDist.x;
    	  map->x += step.x;
    	  side = (ray.x > 0) ? 1 : 2;
    	}
    	else
    	{
    	  sideDist->y += deltDist.y;
    	  map->y += step.y;
		  side = (ray.y > 0) ? 3 : 0;
    	}
    	if (g_mapinfo.map[map->y][map->x] > 0) hit = 1; //1인 경우만 히트
    }
	return side;
}