#include "./cub3d.h"

typedef struct	s_map
{
	int			r;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			s;
	int			f;
	int			c;
	int			wid;
	int			hei;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*s_path;
	int			f_rgb[3];
	int			c_rgb[3];
	
}				t_map;

int map_read(const char *map_path)
{
	int fd;
	int i;
	char **line;
	char **dptr;
	char **dptr2;
	t_map map_info;
	t_list *list;

	//validtest();
	ft_memset(&map_info, 0, sizeof(t_map));
	list = malloc(sizeof(t_list));
	fd = open(map_path, O_RDONLY);
	line = (char **)malloc(sizeof(char *));
	while (get_next_line(fd, line) == 1)//line[0] need free 
	{
		if (*line && map_info.r && map_info.no && map_info.so && map_info.we && map_info.ea
	&& map_info.s && map_info.f && map_info.c)
		{
			//연결리스트
			ft_lstadd_back(&(list->next), ft_lstnew(*line));
		}
		else if (*line != 0)
		{
			dptr = ft_split(*line, ' ');
			if (ft_strncmp("R", dptr[0], sizeof(dptr[0])) == 0)
			{
				map_info.r = 1;
				map_info.wid = ft_atoi(dptr[1]);
				map_info.hei = ft_atoi(dptr[2]);
			}
			else if (ft_strncmp("NO", dptr[0], sizeof(dptr[0])) == 0)
			{
				map_info.no = 1;
				map_info.no_path = ft_strdup(dptr[1]);
			}
			else if (ft_strncmp("SO", dptr[0], sizeof(dptr[0])) == 0)
			{
				map_info.so = 1;
				map_info.so_path = ft_strdup(dptr[1]);
			}
			else if (ft_strncmp("WE", dptr[0], sizeof(dptr[0])) == 0)
			{
				map_info.we = 1;
				map_info.we_path = ft_strdup(dptr[1]);
			}
			else if (ft_strncmp("EA", dptr[0], sizeof(dptr[0])) == 0)
			{
				map_info.ea = 1;
				map_info.ea_path = ft_strdup(dptr[1]);
			}
			else if (ft_strncmp("S", dptr[0], sizeof(dptr[0])) == 0)
			{
				map_info.s = 1;
				map_info.s_path = ft_strdup(dptr[1]);
			}
			else if (ft_strncmp("F", dptr[0], sizeof(dptr[0])) == 0)
			{
				map_info.f = 1;
				dptr2 = ft_split(dptr[1], ',');
				i = -1;
				while (++i < 3)
					map_info.f_rgb[i] = ft_atoi(dptr2[i]);
				//free(dptr2)
			}
			else if (ft_strncmp("C", dptr[0], sizeof(dptr[0])) == 0)
			{
				map_info.f = 1;
				dptr2 = ft_split(dptr[1], ',');
				i = -1;
				while (++i < 3)
					map_info.f_rgb[i] = ft_atoi(dptr2[i]);
				//free(dptr2)
			}
			//free(dptr); 0,1 or 0,1,2
		}
		free(*line);
	}
	//eof 처리
	ft_lstadd_back(&(list->next), ft_lstnew(*line));
	//lst free
	close(fd);
	t_list *curr;
	curr = list->next;
	while (curr->next) {
		printf("%s\n", curr->content);
		curr = curr->next;
	}
	return 0;
}