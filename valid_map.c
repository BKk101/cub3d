/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:29:54 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 17:04:19 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static int	g_dx[] = {0, 0, -1, 1};
static int	g_dy[] = {-1, 1, 0, 0};

int	visit(char **map, int i, int j, t_pos_int size)
{
	int			d;
	t_pos_int	next;

	if (i == 0 || j == 0 || i == size.y - 1
		|| j == size.x - 1 || map[i][j] == ' ')
		return (0);
	map[i][j] = '1';
	d = 0;
	while (d < 4)
	{
		next.x = j + g_dx[d];
		next.y = i + g_dy[d];
		if (map[next.y][next.x] != '1'
			&& !visit(map, next.y, next.x, size))
			return (0);
		++d;
	}
	return (1);
}

int	check_bound(char **map, t_pos_int size)
{
	int r;
	int c;

	r = 0;
	while (r < size.y)
	{
		c = 0;
		while (c < size.x)
		{
			if (map[r][c] != ' ' && map[r][c] != '1' && !visit(map, r, c, size))
				return (0);
			++c;
		}
		++r;
	}
	return (1);
}

int	check_value(char **map, t_pos_int size)
{
	int		i;
	int		j;
	char	dir;

	dir = 0;
	i = -1;
	while (++i < size.y)
	{
		j = -1;
		while (++j < size.x)
		{
			if (ft_strchr(" 012", map[i][j]))
				continue;
			if (!ft_strchr("EWSN", map[i][j]) || dir)
				return (0);
			dir = map[i][j];
		}
	}
	return (dir);
}

int	valid_map(t_mapinfo *m_info, int *flag)
{
	int			ret;
	char		**map;

	if (flag[8])
		return (0);
	flag[8] = 1;
	ret = 1;
	if (m_info->rc.x < 3 || m_info->rc.y < 3)
		ret = 0;
	else
	{
		map = init_map(m_info->map, m_info->rc);
		if (!check_value(map, m_info->rc) || !check_bound(map, m_info->rc))
			ret = 0;
		free_dptr(map, m_info->rc.y);
	}
	return (ret);
}
