/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mapfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:25:49 by bykim             #+#    #+#             */
/*   Updated: 2020/11/02 22:34:38 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static char *g_info[] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};
static char **g_dptr;
static char	**g_dptr2;
static int	g_flag[8]; // r, no, so, we, ea, s, f, c
static int 	g_i;
static int 	g_j;
static int 	g_idx;

static void	read_info(t_mapinfo *map_info, char *line)
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

static void	make_2darr(t_mapinfo *m_info, const char *path)
{
	int		fd;
	char	*line;

	g_i = -1;
	m_info->map = (int **)malloc(sizeof(int *) * m_info->rc.y);
	while (++g_i<m_info->rc.y)
		m_info->map[g_i] = (int *)malloc(sizeof(int) * m_info->rc.x);
	fd = open(path, O_RDONLY);
	ft_memset(g_flag,0,sizeof(g_flag));
	while (get_next_line(fd, &line) == 1)
	{
		if (*line && check_infoflag()) 
			fill_2darr(m_info, line);
		else if (*line)
			read_info(m_info, line);
		free(line);
	}
	if (*line && check_infoflag()) 
		fill_2darr(m_info, line);
	free(line);
}

int	Read_mapfile(t_mapinfo *m_info, const char *map_path)
{
	int		fd;
	char	*line;

	ft_memset(m_info, 0, sizeof(t_mapinfo)); //외부에서 초기화?
	fd = open(map_path, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (*line && check_infoflag())
			m_info->rc.x = ft_strlen(line)>m_info->rc.x ? ft_strlen(line):m_info->rc.x;
		if (*line && check_infoflag())
			m_info->rc.y++;
		else if (*line)
			read_info(m_info, line);
		free(line);
	}
	if (*line && check_infoflag())
		m_info->rc.x = ft_strlen(line)>m_info->rc.x ? ft_strlen(line):m_info->rc.x;
	if (*line && check_infoflag())
		m_info->rc.y++;
	free(line);
	close(fd);
	make_2darr(m_info, map_path);
	return (0);
}
