#include <mlx.h>
#include <stdio.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int             close(int keycode, t_vars *vars)
{
    
	printf("%d\n", keycode);
	//mlx_destroy_window(vars->mlx, vars->win);
	return 0;
}

int main()
{
	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "new window");
	for (int i=0;i<100;i++) {
		for (int j=0;j<10;j++) {
			mlx_pixel_put(vars.mlx, vars.win, 250+j, 250+i, 0xCC66CC);
		}
	}
	mlx_key_hook(vars.win, close, &vars);
	mlx_loop(vars.mlx);
}
