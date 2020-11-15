/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mapfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:25:49 by bykim             #+#    #+#             */
/*   Updated: 2020/11/15 19:19:07 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	read_info(t_mapinfo *m_info, char *line)
{
	int		i;
	char	**temp;

	if (ft_strchr(" 012", line[0]) != 0)
	{
		temp = malloc(sizeof(char *) * (m_info->rc.y + 1));
		i = -1;
		while (++i < m_info->rc.y)
			temp[i] = m_info->map[i];
		temp[i] = ft_strjoin(line, "");
		free(m_info->map);
		m_info->rc.y++;
		m_info->map = temp;
		m_info->rc.x = ft_strlen(line) > m_info->rc.x ?
			ft_strlen(line) : m_info->rc.x;
	}
	else if (ft_strchr("RNSWEFC", line[0]) != 0)
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
		else if (*line && !read_info(m_info, line))
			return (Error("invalid_element"));
		free(line);
		if (ret == 0)
			break ;
	}
	close(fd);
	if (!valid_map(m_info) || !valid_elem(m_info))
		return (Error("invalid_element"));
	return (0);
}
