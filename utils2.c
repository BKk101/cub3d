/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:29:46 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 03:29:46 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	ft_dptrlen(char **dptr)
{
	int len;

	len = 0;
	while (dptr[len])
		len++;
	return (len);
}

int	is_all_digit(const char *s)
{
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

int	count_chars(const char *s, int c)
{
	int cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			++cnt;
		++s;
	}
	return (cnt);
}
