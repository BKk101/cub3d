/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mapfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:25:49 by bykim             #+#    #+#             */
/*   Updated: 2020/08/06 18:02:25 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

char *g_info[] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};
char **g_dptr;
char **g_dptr2;
int g_i;
int g_j;
int g_idx;

void	read_info(t_mapinfo *map_info, char *line)
{
	g_i = 0;
	g_idx = 0;
	g_dptr = ft_split(line, ' ');
	while (ft_strncmp(g_info[g_idx], g_dptr[g_i], sizeof(g_dptr[g_i])) != 0)
		g_idx++;
	map_info->info_flag[g_idx] = 1;
	if (g_idx == 0)
	{
		map_info->win_wid = ft_atoi(g_dptr[++g_i]);
		map_info->win_hei = ft_atoi(g_dptr[++g_i]);
	}
	else if (g_idx == 6 || g_idx == 7)
	{
		g_dptr2 = ft_split(g_dptr[++g_i], ',');
		g_j = -1;
		while (++g_j < 3)
			map_info->fc_rgb[g_idx - 6][g_j] = ft_atoi(g_dptr2[g_j]);
		free_dptr(g_dptr2, g_j - 1);
		free(g_dptr2);
	}
	else
		map_info->path_list[g_idx - 1] = ft_strdup(g_dptr[++g_i]);
	free_dptr(g_dptr, g_i);
	free(g_dptr);
}

int		check_infoflag(t_mapinfo map_info)
{
	int i;

	i = 0;
	while (i < 8 && map_info.info_flag[i])
		i++;
	if (i != 8)
		return (0);
	return (1);
}

void	fill_2darr(t_mapinfo *map, t_list *list)
{
	int len;

	g_i = -1;
	list = list->next;
	while (++g_i < map->row)
	{
		g_j = -1;
		len = ft_strlen(list->content);
		while (++g_j < len)
		{
			map->arr[g_i][g_j] = ((char *)list->content)[g_j] - '0';
			if (((char *)list->content)[g_j] > 68 && ((char *)list->content)[g_j] < 88)
			{
				map->posX = g_j;
				map->posY = g_i;
			}
		}
		if (len < map->col)
			while (len < map->col)
				map->arr[g_i][len++] = -16;
		list = list->next;
	}
}

int		make_2darr(t_mapinfo *map, t_list *list)
{
	t_list *curr;

	map->row = ft_lstsize(list->next);
	map->col = 0;
	map->arr = (int **)malloc(sizeof(int *) * map->row);
	curr = list->next;
	while (curr)
	{
		map->col = ft_strlen((char *)curr->content) > map->col ?
ft_strlen((char *)curr->content) : map->col;
		curr = curr->next;
	}
	while (--map->row >= 0)
		map->arr[map->row] = (int *)malloc(sizeof(int) * map->col);
	map->row = ft_lstsize(list->next);
	fill_2darr(map, list);
	return (0);
}

int		read_mapfile(t_mapinfo *map_info, const char *map_path)
{
	int		fd;
	char	*line;
	t_list	*list;

	ft_memset(map_info, 0, sizeof(t_mapinfo));
	list = malloc(sizeof(t_list));
	ft_memset(list, 0, sizeof(t_list));
	fd = open(map_path, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (*line && check_infoflag(*map_info))
			ft_lstadd_back(&(list->next), ft_lstnew(line));
		else if (*line)
			read_info(map_info, line);
	}
	ft_lstadd_back(&(list->next), ft_lstnew(line));
	close(fd);
	make_2darr(map_info, list);
	return (0);
}
