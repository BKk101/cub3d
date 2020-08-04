#include "./cub3d.h"

void	free_dptr(char **start, int len)
{
	int i;

	i = -1;
	while (++i <= len)
		free(*(start + i));
}