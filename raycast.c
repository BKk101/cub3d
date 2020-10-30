#include "./cub3d.h"

int		raycast(t_vars *vars)
{
	int w = vars->m_info->win.x;
	int h = vars->m_info->win.y;
	double posX = vars->m_info->pos.x, posY = vars->m_info->pos.y;

	for(int x = 0; x < w; x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = vars->r_info->dir.x + vars->r_info->plane.x * cameraX;
		double rayDirY = vars->r_info->dir.y + vars->r_info->plane.y * cameraX;

		int mapX = (int)posX;
		int mapY = (int)posY;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
    	if (rayDirX < 0)
    	{
    	  stepX = -1;
    	  sideDistX = (posX - mapX) * deltaDistX;
    	}
    	else
    	{
    	  stepX = 1;
    	  sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    	}
    	if (rayDirY < 0)
    	{
    	  stepY = -1;
    	  sideDistY = (posY - mapY) * deltaDistY;
    	}
    	else
    	{
    	  stepY = 1;
    	  sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    	}
		//perform DDA
      	while (hit == 0)
      	{
        	//jump to next map square, OR in x-direction, OR in y-direction
        	if (sideDistX < sideDistY)
        	{
        	  sideDistX += deltaDistX;
        	  mapX += stepX;
        	  side = 0;
        	}
        	else
        	{
        	  sideDistY += deltaDistY;
        	  mapY += stepY;
        	  side = 1;
        	}
        	//Check if ray has hit a wall
        	if (vars->m_info->map[mapY][mapX] > 0) hit = 1;
    	}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    	if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    	else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
      	int lineHeight = perpWallDist == 0 ? (int)h : (int)(h / perpWallDist);

      	//calculate lowest and highest pixel to fill in current stripe
      	int drawStart = -lineHeight / 2 + h / 2;
      	if(drawStart < 0)drawStart = 0;
      	int drawEnd = lineHeight / 2 + h / 2;
      	if(drawEnd >= h)drawEnd = h - 1;

		//choose wall color
      	int color;
      	switch(vars->m_info->map[mapY][mapX])
      	{
      	  case 1:  color = 0xFF0000;  break; //red
      	  case 2:  color = 0x00FF00;  break; //green
      	  case 3:  color = 0x0000FF;   break; //blue
      	  case 4:  color = 0xFFFFFF;  break; //white
      	  default: color = 0xFFFF00; break; //yellow
      	}
		//printf("%d %d\n", x, color);
      	//give x and y sides different brightness
      	//if (side == 1) {color = color / 2;}

      	//draw the pixels of the stripe as a vertical line
		for (int y=drawStart;y<=drawEnd;y++)
			mlx_pixel_put(vars->mlx->mlx, vars->mlx->win, x, y, color);

	}

	vars->r_info->oldTime = vars->r_info->time;
    vars->r_info->time = clock();
    vars->r_info->frameTime = (vars->r_info->time - vars->r_info->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	vars->r_info->moveSpeed = vars->r_info->frameTime * 0.05; //the constant value is in squares/second
    vars->r_info->rotSpeed = vars->r_info->frameTime * 0.03; //the constant value is in radians/second
	return 0;
}