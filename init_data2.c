/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:29:09 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 17:28:04 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	init_mapdata(t_mapinfo *m_info)
{
	int i;
	int j;

	i = -1;
	while (++i < m_info->rc.y)
	{
		j = -1;
		while (++j < (int)ft_strlen(m_info->map[i]))
		{
			if (ft_strchr("NEWS", m_info->map[i][j]) != 0)
			{
				m_info->news = m_info->map[i][j];
				m_info->pos.x = j + 0.5;
				m_info->pos.y = i + 0.5;
				m_info->map[i][j] = '0';
				return ;
			}
		}
	}
}

char	**init_map(char **strs, t_pos_int size)
{
	char	**map;
	int		i;
	int		j;

	map = malloc(sizeof(char *) * size.y);
	i = -1;
	while (++i < size.y)
	{
		map[i] = malloc(size.x);
		ft_memset(map[i], ' ', size.x);
	}
	i = -1;
	while (++i < size.y)
	{
		j = (int)ft_strlen(strs[i]);
		while (--j >= 0)
			map[i][j] = strs[i][j];
	}
	return (map);
}
