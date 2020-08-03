#include "./cub3d.h"

char *g_info[] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};

void	free_dptr(char **start, int len)
{
	int i;

	i = -1;
	while (++i <= len)
		free(*(start + i));
}

void	read_info(t_map *map_info, char *line)
{
	int i;
	int j;
	int idx;
	char **dptr;
	char **dptr2;

	i = 0;
	idx = 0;
	dptr = ft_split(line, ' ');
	while (ft_strncmp(g_info[idx], dptr[i], sizeof(dptr[i])) != 0)
		idx++;
	map_info->info_list[idx] = 1;
	if (idx == 0)
	{
		map_info->wid = ft_atoi(dptr[++i]);
		map_info->hei = ft_atoi(dptr[++i]);
	}
	else if (idx == 6 || idx == 7)
	{
		dptr2 = ft_split(dptr[++i], ',');
		j = -1;
		while (++j < 3)
			map_info->rgb[idx - 6][j] = ft_atoi(dptr2[j]);
		free_dptr(dptr2, j - 1);
		free(dptr2);
	}
	else
		map_info->path_list[idx - 1] = ft_strdup(dptr[++i]);
	free_dptr(dptr, i);
	free(dptr);
}

int		map_info_check(t_map map_info)
{
	int i;

	i = 0;
	while (i < 8 && map_info.info_list[i])
		i++;
	if (i != 8)
		return 0;
	return 1;
}

int		map_read(t_map *map_info, t_list **list, const char *map_path)
{
	int fd;
	char *line;

	//mpavalidtest();
	ft_memset(map_info, 0, sizeof(t_map));
	*list = malloc(sizeof(t_list));
	ft_memset(*list, 0, sizeof(t_list));
	fd = open(map_path, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (*line && map_info_check(*map_info))
			ft_lstadd_back(&((*list)->next), ft_lstnew(line));
		else if (*line)
			read_info(map_info, line);
	}
	ft_lstadd_back(&((*list)->next), ft_lstnew(line));
	//lst free
	close(fd);
	return 0;
}