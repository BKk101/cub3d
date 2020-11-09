#include "./cub3d.h"

int	Keyboard(int keycode, t_vars *vars)
{
	if (keycode == 53) //esc
	{
		mlx_destroy_window(g_mlx.mlx, g_mlx.win);
		exit(0);
	}
	else if (keycode == 13) //w
    {
		printf("W is pressed  x=%.2lf y=%.2lf\n", vars->player.pos.x, vars->player.pos.y);
		vars->player.move = 'W';
    }
    else if (keycode == 0) //a
    {
      	printf("A is pressed  x=%.2lf y=%.2lf\n", vars->player.pos.x, vars->player.pos.y);
		vars->player.move = 'A';
    }
	else if (keycode == 1) //s
    {
      	printf("S is pressed  x=%.2lf y=%.2lf\n", vars->player.pos.x, vars->player.pos.y);
		vars->player.move = 'S';
    }
	else if (keycode == 2) //d
    {
      	printf("D is pressed  x=%.2lf y=%.2lf\n", vars->player.pos.x, vars->player.pos.y);
		vars->player.move = 'D';
    }
    else if (keycode == 124) //right
    {
    	printf("right is pressed  x=%.2lf y=%.2lf\n", vars->player.pos.x, vars->player.pos.y);
		vars->player.move = 'R';
	}
    else if (keycode == 123) //left
    {
        printf("left is pressed  x=%.2lf y=%.2lf\n", vars->player.pos.x, vars->player.pos.y);
		vars->player.move = 'L';
    }
	return 0;
}

int Mouse(int button, int x, int y, t_vars *vars)
{
	printf("%d x:%d y:%d\n", button, x, y);
	return 0;
}
