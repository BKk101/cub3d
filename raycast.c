#include "./cub3d.h"

int		raycast(t_vars *vars)
{
	t_pos_int i;
	t_pos_int screen;
	t_pos_int map;
	t_pos_int step;
	t_pos_doub ray;
	t_pos_doub sideDist;
	t_pos_doub deltDist;
	int hit;
	int side;
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
		
		deltDist.x = fabs(1 / ray.x);
		deltDist.y = fabs(1 / ray.y);
	
		hit = 0; //was there a wall hit?
		
		//calculate step and initial sideDist
		Calc_step_sidedist(ray.x, vars->m_info->pos.x, &step.x, &sideDist.x);
		Calc_step_sidedist(ray.y, vars->m_info->pos.y, &step.y, &sideDist.y);
    	
		/*if (ray.x < 0)
    	{
    	  	step.x = -1;
    	  	sideDist.x = (vars->m_info->pos.x - map.x) * deltDist.x;
    	}
    	else
    	{
    	  	step.x = 1;
    	  	sideDist.x = (map.x + 1 - vars->m_info->pos.x) * deltDist.x;
    	}
    	if (ray.y < 0)
		{
			step.y = -1;
    		sideDist.y = (vars->m_info->pos.y - map.y) * deltDist.y;
    	}
    	else 
		{
			step.y = 1;
    	  	sideDist.y = (map.y + 1 - vars->m_info->pos.y) * deltDist.y;
    	}
		*/
		//perform DDA
      	while (hit == 0)
      	{
        	//jump to next map square, OR in x-direction, OR in y-direction
        	if (sideDist.x < sideDist.y)
        	{
        	  sideDist.x += deltDist.x;
        	  map.x += step.x;
        	  side = 0;
        	}
        	else
        	{
        	  sideDist.y += deltDist.y;
        	  map.y += step.y;
			  side = 1;
        	}
        	if (vars->m_info->map[map.y][map.x] > 0) hit = 1; //1인 경우만 히트
    	}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    	if (side == 0) pWallDist = (map.x - vars->m_info->pos.x + (1 - step.x) / 2) / ray.x;
		else           pWallDist = (map.y - vars->m_info->pos.y + (1 - step.y) / 2) / ray.y;

		//Calculate height of line to draw on screen
      	int lineHeight = pWallDist == 0 ? (int)screen.y : (int)(screen.y / pWallDist);

      	//calculate lowest and highest pixel to fill in current stripe
      	int drawStart = -lineHeight / 2 + screen.y / 2;
      	if(drawStart < 0)drawStart = 0;
      	int drawEnd = lineHeight / 2 + screen.y / 2;
      	if(drawEnd >= screen.y)drawEnd = screen.y - 1;

		//choose wall color
      	int color;
      	switch(vars->m_info->map[map.y][map.x])
      	{
      	  case 1:  color = 0xFF0000;  break; //red
      	  case 2:  color = 0x00FF00;  break; //green
      	  case 3:  color = 0x0000FF;   break; //blue
      	  case 4:  color = 0xFFFFFF;  break; //white
      	  default: color = 0xFFFF00; break; //yellow
      	}
      	//give x and y sides different brightness
      	if (side == 1) {color = color / 2;}

      	//draw the pixels of the stripe as a vertical line
		for (i.y=drawStart;i.y<=drawEnd;i.y++)
			mlx_pixel_put(vars->mlx->mlx, vars->mlx->win, i.x, i.y, color);

	}
    vars->r_info->frameTime = ((double)clock()- time) / CLOCKS_PER_SEC; //frameTime is the time this frame has taken, in seconds
	vars->r_info->moveSpeed = vars->r_info->frameTime * 30; //the constant value is in squares/second
    vars->r_info->rotSpeed = vars->r_info->frameTime * 10; //the constant value is in radians/second

	if (vars->r_info->key == 'U' || vars->r_info->key == 'D') 
		Move(&vars->m_info->pos, vars->r_info->key);
	else if (vars->r_info->key == 'R' || vars->r_info->key == 'L') 
	{
		Rotate(&vars->r_info->dir, vars->r_info->key);
		Rotate(&vars->r_info->plane, vars->r_info->key);
	}
	vars->r_info->key = 0;
	return 0;
}

void Calc_step_sidedist(double ray, double pos, int *step, double *sideDist)
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
}