#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
	int			color;
	clock_t		start;

}               t_vars;

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
	return 0;
}

int mouse(int button, int x, int y, t_vars *vars)
{
	printf("%d x:%d y:%d\n", button, x, y);
	return 0;
}

int render_next_frame(t_vars *vars)
{
	int rainbow[7][3] = {{255,000,000}, {255,102,000}, {255,255,000},
{000,255,000},{000,000,255},{000,000,102},{127,000,255}};
	
	int s = (clock() - vars->start) / 100000;
	int a = s % 7;
	vars->color = create_trgb(0, rainbow[a][0], rainbow[a][1], rainbow[a][2]);
	for (int i=0;i<250;i++) {
		for (int j=0;j<10;j++) {
			mlx_pixel_put(vars->mlx, vars->win, 125+i, 250+j, vars->color);
		}
	}
	return 0;
}

int main()
{
	t_vars vars;

	vars.color = create_trgb(0,255,100,170);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "new window");
	vars.start = clock();

	//mlx_key_hook(vars.win, keyboard, &vars);
	//mlx_mouse_hook(vars.win, mouse, &vars);
	mlx_hook(vars.win, 2, 1L<<0, keyboard, &vars);
	mlx_hook(vars.win, 4, 1L<<2, mouse, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
