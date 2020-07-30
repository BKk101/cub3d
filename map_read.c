#include "./cub3d.h"

void	free_dptr(char **start, int len)
{
	int i;

	i = -1;
	while (++i <= len)
		free(*(start + i));
}

int		map_read(const char *map_path)
{
	int fd;
	int i;
	int j;
	char *line;
	char **dptr;
	char **dptr2;
	t_map map_info;
	t_list *list;

	//mpavalidtest();
	ft_memset(&map_info, 0, sizeof(t_map));
	list = malloc(sizeof(t_list));
	ft_memset(list, 0, sizeof(t_list));
	fd = open(map_path, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (*line && map_info.r && map_info.no && map_info.so && map_info.we && map_info.ea
	&& map_info.s && map_info.f && map_info.c)
		{
			ft_lstadd_back(&(list->next), ft_lstnew(line));
		}
		else if (*line)
		{
			i = 0;
			dptr = ft_split(line, ' ');
			if (ft_strncmp("R", dptr[i], sizeof(dptr[i])) == 0)
			{
				map_info.r = 1;
				map_info.wid = ft_atoi(dptr[++i]);
				map_info.hei = ft_atoi(dptr[++i]);
			}
			else if (ft_strncmp("NO", dptr[i], sizeof(dptr[i])) == 0)
			{
				map_info.no = 1;
				map_info.no_path = ft_strdup(dptr[++i]);
			}
			else if (ft_strncmp("SO", dptr[i], sizeof(dptr[i])) == 0)
			{
				map_info.so = 1;
				map_info.so_path = ft_strdup(dptr[++i]);
			}
			else if (ft_strncmp("WE", dptr[i], sizeof(dptr[i])) == 0)
			{
				map_info.we = 1;
				map_info.we_path = ft_strdup(dptr[++i]);
			}
			else if (ft_strncmp("EA", dptr[i], sizeof(dptr[i])) == 0)
			{
				map_info.ea = 1;
				map_info.ea_path = ft_strdup(dptr[++i]);
			}
			else if (ft_strncmp("S", dptr[i], sizeof(dptr[i])) == 0)
			{
				map_info.s = 1;
				map_info.s_path = ft_strdup(dptr[++i]);
			}
			else if (ft_strncmp("F", dptr[i], sizeof(dptr[i])) == 0)
			{
				map_info.f = 1;
				dptr2 = ft_split(dptr[++i], ',');
				j = -1;
				while (++j < 3)
					map_info.f_rgb[j] = ft_atoi(dptr2[j]);
				//free(dptr2)
			}
			else if (ft_strncmp("C", dptr[i], sizeof(dptr[i])) == 0)
			{
				map_info.c = 1;
				dptr2 = ft_split(dptr[++i], ',');
				j = -1;
				while (++j < 3)
					map_info.c_rgb[j] = ft_atoi(dptr2[j]);
				//free(dptr2)
			}
			free_dptr(dptr, i);
			free(dptr);
		}
		free(line);
	}
	ft_lstadd_back(&(list->next), ft_lstnew(line));
	free(line);
	//lst free
	close(fd);
	t_list *curr;
	curr = list->next;
	while (curr) {
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
	return 0;
}