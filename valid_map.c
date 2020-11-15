#include "./cub3d.h"

int			g_i;
int			g_j;
int			g_dx[4] = {0, 0, -1, 1};
int			g_dy[4] = {-1, 1, 0, 0};
int			g_rp;
int			g_wp;
char		**g_dptr;
t_pos_doub	g_nq;
t_pos_doub	g_q;

int	make_2darr(t_mapinfo *m_info)
{
	g_i = -1;
	g_dptr = malloc(sizeof(char *) * m_info->rc.y);
	while (++g_i < m_info->rc.y)
	{
		g_dptr[g_i] = malloc(sizeof(char) * m_info->rc.x);
		g_j = -1;
		while (++g_j < ft_strlen(m_info->map[g_i]))
			g_dptr[g_i][g_j] = m_info->map[g_i][g_j];
		while (g_j < m_info->rc.x)
			g_dptr[g_i][g_j++] = ' ';
	}
	free_dptr(m_info->map, m_info->rc.y);
	m_info->map = g_dptr;
	return (0);
}

int	check_value(t_mapinfo *m_info)
{
	g_i = -1;
	while (++g_i < m_info->rc.y)
	{
		g_j = -1;
		while (++g_j < m_info->rc.x)
		{
			if (ft_strchr(" 012", m_info->map[g_i][g_j]) != 0)
				continue ;
			if (ft_strchr("NEWS", m_info->map[g_i][g_j]) != 0)
			{
				m_info->news = m_info->map[g_i][g_j];
				m_info->pos.x = g_j;
				m_info->pos.y = g_i;
				m_info->map[g_i][g_j] = '0';
			}
			else
				return (0);
		}
	}
	return (m_info->news != 0);
}

int	check_bound(t_mapinfo *m_info, t_pos_doub *que, int visit[][g_mapinfo.rc.x])
{
	que[g_rp++] = m_info->pos;
	visit[(int)m_info->pos.y][(int)m_info->pos.x] = 1;
	while (g_rp < g_wp)
	{
		g_q = que[g_wp++];
		g_i = -1;
		while (++g_i < 4)
		{
			g_nq.x = (int)g_q.x + g_dx[g_i];
			g_nq.y = (int)g_q.y + g_dy[g_i];
			if (g_nq.y < 1 || g_nq.y >= m_info->rc.y - 1 || g_nq.x < 1 ||
g_nq.x >= m_info->rc.x || m_info->map[(int)g_nq.y][(int)g_nq.x] == ' ')
				return (0);
			if (visit[(int)g_nq.y][(int)g_nq.x] == 1 ||
				m_info->map[(int)g_nq.y][(int)g_nq.x] == '1')
				continue;
			que[g_rp++] = g_nq;
			visit[(int)g_nq.y][(int)g_nq.x] = 1;
		}
	}
	return (1);
}

int	valid_map(t_mapinfo *m_info)
{
	t_pos_doub	que[m_info->rc.x * m_info->rc.y];
	int			visit[m_info->rc.y][m_info->rc.x];

	ft_bzero(que, sizeof(que));
	ft_bzero(visit, sizeof(visit));
	if (m_info->rc.x < 3 || m_info->rc.y < 3)
		return (0);
	else
	{
		make_2darr(m_info);
		if (!check_value(m_info) || !check_bound(m_info, que, visit))
			return (0);
	}
	return (1);
}
