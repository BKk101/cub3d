#include "./cub3d.h"

char *g_info[] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};
char **g_dptr;
char **g_dptr2;
int g_i;
int g_j;
int g_idx;

void	free_dptr(char **start, int len)
{
	int i;

	i = -1;
	while (++i <= len)
		free(*(start + i));
}

void	read_info(t_map *map_info, char *line)
{
	g_i = 0;
	g_idx = 0;
	g_dptr = ft_split(line, ' ');
	while (ft_strncmp(g_info[g_idx], g_dptr[g_i], sizeof(g_dptr[g_i])) != 0)
		g_idx++;
	map_info->info_list[g_idx] = 1;
	if (g_idx == 0)
	{
		map_info->wid = ft_atoi(g_dptr[++g_i]);
		map_info->hei = ft_atoi(g_dptr[++g_i]);
	}
	else if (g_idx == 6 || g_idx == 7)
	{
		g_dptr2 = ft_split(g_dptr[++g_i], ',');
		g_j = -1;
		while (++g_j < 3)
			map_info->rgb[g_idx - 6][g_j] = ft_atoi(g_dptr2[g_j]);
		free_dptr(g_dptr2, g_j - 1);
		free(g_dptr2);
	}
	else
		map_info->path_list[g_idx - 1] = ft_strdup(g_dptr[++g_i]);
	free_dptr(g_dptr, g_i);
	free(g_dptr);
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

void	fill_2darr(t_list *list, int ***arr, int col, int row)
{
	int len;

	g_idx = -1;
	list = list->next;
	while (++g_idx < col)
	{
		g_i = -1;
		len = ft_strlen(list->content);
		while (++g_i < len)
			*arr[g_idx][g_i] = ((char *)list->content)[g_i] - '0';
		if (len < row)
			while (len < row)
				*arr[g_idx][len++] = -16;
		list = list->next;
	}
}

int		**make_2darr(t_list *list)
{
	int	**arr;
	t_list *curr;

	g_i = ft_lstsize(list->next);
	g_j = 0;
	arr = (int **)malloc(sizeof(int *) * g_i);
	curr = list->next;
	while (curr)
	{
		g_j = ft_strlen((char *)curr->content) > g_j ? ft_strlen((char *)curr->content) : g_j;
		curr = curr->next;
	}
	while (--g_i >= 0)
		arr[g_i] = (int *)malloc(sizeof(int) * g_j);
	g_i = ft_lstsize(list->next);
	fill_2darr(list, &arr, g_i, g_j);
	return (arr);
}

int		map_read(t_map *map_info, int ***map, const char *map_path)
{
	int		fd;
	char	*line;
	t_list	*list;

	//mpavalidtest();
	ft_memset(map_info, 0, sizeof(t_map));
	list = malloc(sizeof(t_list));
	ft_memset(list, 0, sizeof(t_list));
	fd = open(map_path, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (*line && map_info_check(*map_info))
			ft_lstadd_back(&(list->next), ft_lstnew(line));
		else if (*line)
			read_info(map_info, line);
	}
	ft_lstadd_back(&(list->next), ft_lstnew(line));
	close(fd);
	*map = make_2darr(list);
	return 0;
}