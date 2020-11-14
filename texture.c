#include "./cub3d.h"

int	load_texture(t_texture *texture, char *file_path)
{
	int		tmp;
	void	*img;

	img = mlx_xpm_file_to_image(g_mlx.mlx, file_path,
		&texture->size.x, &texture->size.y);
	if (!img)
		return (0);
	texture->data = (int *)mlx_get_data_addr(img, &tmp, &tmp, &tmp);
	return (texture->data != 0);
}
