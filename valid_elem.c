#include "./cub3d.h"

char	*g_elem[8] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};

int	get_resolution(t_mapinfo *m_info, char **str)
{
	if (!is_all_digit(str[1]) || !is_all_digit(str[2]))
		return (0);
	m_info->win.x = ft_atoi(str[1]);
	m_info->win.y = ft_atoi(str[2]);
	return (1);
}

int	get_fc(t_mapinfo *m_info, char **str, int idx)
{
	int		i;
	int		ret;
	int		cnt;
	char	**substr;

	ret = 0;
	substr = ft_split(str[1], ',');
	if ((count_chars(str[1], ',') == 2) && (cnt = ft_dptrlen(substr)) == 3)
	{
		i = -1;
		while (++i < 3)
		{
			if (!is_all_digit(substr[i]) || ft_atoi(substr[i]) > 255)
				break ;
			m_info->fc_rgb[idx - 6][i] = ft_atoi(substr[i]);
		}
		ret = (i == 3);
		free_dptr(substr, cnt);
	}
	return (ret);
}

int	get_texture(t_mapinfo *m_info, char **str, int idx)
{
	m_info->path_list[idx - 1] = ft_strdup(str[1]);
	return (1);
}

int	check_info(t_mapinfo *m_info, char **str, int idx, int *flag)
{
	int len;
	int ret;

	ret = 1;
	len = ft_dptrlen(str);
	if (flag[idx])
		return (0);
	flag[idx] = 1;
	if (idx == 0)
	{
		if (len != 3 || !get_resolution(m_info, str))
			ret = 0;
	}
	else if (idx == 6 || idx == 7)
	{
		if (len != 2 || !get_fc(m_info, str, idx))
			ret = 0;
	}
	else
	{
		if (len != 2 || !get_texture(m_info, str, idx))
			ret = 0;
	}
	return (ret);
}

int	valid_elem(t_mapinfo *m_info, int *flag)
{
	char	**substr;
	int		ret;
	int		i;
	int		j;

	if (m_info->elem_num != 8)
		return (0);
	i = -1;
	ret = 1;
	while (++i < m_info->elem_num && ret)
	{
		substr = ft_split(m_info->elem[i], ' ');
		j = 0;
		while (j < 8 && ft_strncmp(g_elem[j], substr[0],
			ft_strlen(substr[0]) + 1))
			j++;
		if (j >= 8 || !check_info(m_info, substr, j, flag))
			ret = 0;
		free_dptr(substr, ft_dptrlen(substr));
	}
	return (ret);
}
