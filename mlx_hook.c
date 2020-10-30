#include "./cub3d.h"

int	keyboard(int keycode, t_vars *vars)
{
	mlx_clear_window(vars->mlx->mlx, vars->mlx->win);
	if (keycode == 53) //esc
	{
		mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
		exit(0);
	}
	else if (keycode == 126) //up
    {
      printf("up is pressed  %lf\n", vars->r_info->frameTime);
	  if(vars->m_info->map[(int)(vars->m_info->pos.y)][(int)(vars->m_info->pos.x + vars->r_info->dir.x * vars->r_info->moveSpeed)] == 0) vars->m_info->pos.x += vars->r_info->dir.x * vars->r_info->moveSpeed;
      if(vars->m_info->map[(int)(vars->m_info->pos.y + vars->r_info->dir.y * vars->r_info->moveSpeed)][(int)(vars->m_info->pos.x)] == 0) vars->m_info->pos.y += vars->r_info->dir.y * vars->r_info->moveSpeed;
    }
    //move backwards if no wall behind you
    else if (keycode == 125) //down
    {
      printf("down is pressed  %lf\n", vars->r_info->frameTime);
	  if(vars->m_info->map[(int)(vars->m_info->pos.y)][(int)(vars->m_info->pos.x - vars->r_info->dir.x * vars->r_info->moveSpeed)] == 0) vars->m_info->pos.x -= vars->r_info->dir.x * vars->r_info->moveSpeed;
      if(vars->m_info->map[(int)(vars->m_info->pos.y - vars->r_info->dir.y * vars->r_info->moveSpeed)][(int)(vars->m_info->pos.x)] == 0) vars->m_info->pos.y -= vars->r_info->dir.y * vars->r_info->moveSpeed;
    }
    //rotate to the right
    else if (keycode == 124) //right
    {
      //both camera direction and camera plane must be rotated
      printf("right is pressed  %lf\n", vars->r_info->frameTime);
	  double oldDirX = vars->r_info->dir.x;
      vars->r_info->dir.x = vars->r_info->dir.x * cos(-vars->r_info->rotSpeed) - vars->r_info->dir.y * sin(-vars->r_info->rotSpeed);
      vars->r_info->dir.y = oldDirX * sin(-vars->r_info->rotSpeed) + vars->r_info->dir.y * cos(-vars->r_info->rotSpeed);
      double oldPlaneX = vars->r_info->plane.x;
      vars->r_info->plane.x = vars->r_info->plane.x * cos(-vars->r_info->rotSpeed) - vars->r_info->plane.y * sin(-vars->r_info->rotSpeed);
      vars->r_info->plane.y = oldPlaneX * sin(-vars->r_info->rotSpeed) + vars->r_info->plane.y * cos(-vars->r_info->rotSpeed);
    }
    //rotate to the left
    else if (keycode == 123) //left
    {
      //both camera direction and camera plane must be rotated
      printf("left is pressed  %lf\n", vars->r_info->frameTime);
	  double oldDirX = vars->r_info->dir.x;
      vars->r_info->dir.x = vars->r_info->dir.x * cos(vars->r_info->rotSpeed) - vars->r_info->dir.y * sin(vars->r_info->rotSpeed);
      vars->r_info->dir.y = oldDirX * sin(vars->r_info->rotSpeed) + vars->r_info->dir.y * cos(vars->r_info->rotSpeed);
      double oldPlaneX = vars->r_info->plane.x;
      vars->r_info->plane.x = vars->r_info->plane.x * cos(vars->r_info->rotSpeed) - vars->r_info->plane.y * sin(vars->r_info->rotSpeed);
      vars->r_info->plane.y = oldPlaneX * sin(vars->r_info->rotSpeed) + vars->r_info->plane.y * cos(vars->r_info->rotSpeed);
    }
	return 0;
}

int mouse(int button, int x, int y, t_vars *vars)
{
	printf("%d x:%d y:%d\n", button, x, y);
	return 0;
}