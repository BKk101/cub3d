#include "./cub3d.h"

// r, no, so, we, ea, s, f, c

int	load_texture(t_texture *texture, char *file_path)
{
	int		tmp;
	void	*img;

	img = mlx_xpm_file_to_image(g_mlx.mlx,file_path,&texture->size.x,&texture->size.y);
	if (!img)
		return (0);
	texture->data = (int *)mlx_get_data_addr(img, &tmp, &tmp, &tmp); //tmp 미사용
	return (texture->data != 0); //?
}

int		parse_key_texture(t_vars *vars, char **path)
{
	int ret;
	int i;

	i = -1;
	while (++i<5)
	{
		ret = load_texture(&vars->texture[i], path[i]);
	}
	//if (!ret)
		//print_error(cuberror(invlid_texture_file));
	return (ret);
}
