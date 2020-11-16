/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mapfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:25:49 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 15:45:38 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static int	g_flag[9];
static int	g_mflag;

int	read_info(t_mapinfo *m_info, char *line)
{
	int		i;
	char	**temp;

	if (ft_strchr(" 012", line[0]) != 0)
	{
		g_mflag = 1;
		temp = malloc(sizeof(char *) * (m_info->rc.y + 1));
		i = -1;
		while (++i < m_info->rc.y)
			temp[i] = m_info->map[i];
		temp[i] = ft_strjoin(line, "");
		free(m_info->map);
		m_info->rc.y++;
		m_info->map = temp;
		m_info->rc.x = (int)ft_strlen(line) > m_info->rc.x ?
			(int)ft_strlen(line) : m_info->rc.x;
	}
	else if (ft_strchr("RNSWEFC", line[0]) != 0 && m_info->elem_num < 9
		&& !g_mflag)
		m_info->elem[m_info->elem_num++] = ft_strjoin(line, "");
	else
		return (0);
	return (1);
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

int	read_mapfile(t_mapinfo *m_info, char *map_path)
{
	int		fd;
	int		ret;
	char	*line;

	if (!check_name(map_path))
		return (print_error("invalid_file_name"));
	if ((fd = open(map_path, O_RDONLY)) == -1)
		return (print_error(strerror(errno)));
	while (1)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return (print_error("file read error"));
		else if (*line && !read_info(m_info, line))
			return (print_error("invalid_element"));
		free(line);
		if (ret == 0)
			break ;
	}
	close(fd);
	if (!valid_map(m_info, g_flag) || !valid_elem(m_info, g_flag))
		return (print_error("invalid_element"));
	return (0);
}
