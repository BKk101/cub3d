/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mapfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:25:49 by bykim             #+#    #+#             */
/*   Updated: 2020/11/15 02:36:10 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static char *g_info[8] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};
static char **g_dptr;
static char	**g_dptr2;
static int	g_flag[8]; // r, no, so, we, ea, s, f, c
static int 	g_i;
static int 	g_j;
static int 	g_idx;

void	read_info(t_mapinfo *map_info, char *line)
{
	g_i = 0;
	g_idx = 0;
	g_dptr = ft_split(line, ' ');
	while (ft_strncmp(g_info[g_idx], g_dptr[g_i], sizeof(g_dptr[g_i])) != 0)
		g_idx++;
	g_flag[g_idx] = 1;
	if (g_idx == 0)
	{
		map_info->win.x = ft_atoi(g_dptr[++g_i]);
		map_info->win.y = ft_atoi(g_dptr[++g_i]);
	}
	else if (g_idx == 6 || g_idx == 7)
	{
		g_dptr2 = ft_split(g_dptr[++g_i], ',');
		g_j = -1;
		while (++g_j < 3)
			map_info->fc_rgb[g_idx - 6][g_j] = ft_atoi(g_dptr2[g_j]);
		free_dptr(g_dptr2, g_j - 1);
		free(g_dptr2);	}
	else
		map_info->path_list[g_idx - 1] = ft_strdup(g_dptr[++g_i]);
	free_dptr(g_dptr, g_i);
	free(g_dptr);
}

static int	check_infoflag(void)
{
	g_i = 0;
	while (g_i < 8 && g_flag[g_i])
		g_i++;
	if (g_i != 8)
		return (0);
	return (1);
}

static void	fill_2darr(t_mapinfo *m_info, char *line)
{
	static int i = -1;
	int len;

	i++;
	g_j = -1;
	len = ft_strlen(line);
	while (++g_j < len) 
	{
		m_info->map[i][g_j] = line[g_j] - '0';
		if (ft_isalpha(line[g_j]))
		{
			m_info->pos.x = g_j;
			m_info->pos.y = i;
			m_info->news = line[g_j];
			m_info->map[i][g_j] = 0;
		}
	}
	if (len < m_info->rc.x)
		while (len < m_info->rc.x)
			m_info->map[i][len++] = -16; // -> space - '0' = -1
}

int	make_2darr(t_mapinfo *m_info, char *path)
{
	int		fd;
	int		ret;
	char	*line;

	g_i = -1;
	m_info->map = (int **)malloc(sizeof(int *) * m_info->rc.y);
	while (++g_i<m_info->rc.y)
		m_info->map[g_i] = (int *)malloc(sizeof(int) * m_info->rc.x);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (Error(strerror(errno)));
	ft_bzero(g_flag, sizeof(g_flag));
	while (1)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return (Error("file read error"));
		if (*line && check_infoflag()) 
			fill_2darr(m_info, line);
		else if (*line)
			read_info(m_info, line);
		free(line);
		if (ret == 0)
			break;
	}
	close(fd);
	return (0);
}

int	check_name(char *map_path)
{
	int	len;
	int	ret;

	if ((len = (int)ft_strlen(map_path)) < 4)
		return (0);
	ret = ft_strncmp(map_path + len - 4, ".cub", 4);
	return (ret == 0);
}

int	Read_mapfile(t_mapinfo *m_info, char *map_path)
{
	int		fd;
	int		ret;
	char	*line;

	if (!check_name(map_path))
		return (Error("invalid_file_name"));
	if ((fd = open(map_path, O_RDONLY)) == -1)
		return (Error(strerror(errno)));
	while (1)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return (Error("file read error"));
		if (*line && check_infoflag())
			m_info->rc.x = ft_strlen(line)>m_info->rc.x ? ft_strlen(line):m_info->rc.x;
		if (*line && check_infoflag())
			m_info->rc.y++;
		else if (*line)
			read_info(m_info, line);
		free(line);
		if (ret == 0)
			break;
	}
	close(fd);
	return (make_2darr(m_info, map_path));
}
