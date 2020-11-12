#include "./cub3d.h"

void	free_dptr(char **start, int len)
{
	int i;

	i = -1;
	while (++i <= len)
		free(*(start + i));
}

int		ft_max(int a, int b)
{
	return (a > b ? a : b);
}

int		ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int		Error(char *s)
{
	perror(s);
	return (-1);
}
