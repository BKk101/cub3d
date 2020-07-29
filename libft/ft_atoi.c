/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:43:37 by bykim             #+#    #+#             */
/*   Updated: 2020/04/13 22:15:28 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getnum(const char *str)
{
	int num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num);
}

static int	ft_minus(const char str, int *ptr)
{
	*ptr = 1;
	if (str == '+')
		return (1);
	else
		return (-1);
}

int			ft_atoi(const char *str)
{
	int flag1;
	int neg;

	flag1 = 0;
	neg = 1;
	while (!(*str >= '0' && *str <= '9'))
	{
		if ((*str > 8 && *str < 14) || *str == 32)
		{
			if (flag1)
				return (0);
		}
		else if (*str == '-' || *str == '+')
		{
			if (!flag1)
				neg = ft_minus(*str, &flag1);
			else
				return (0);
		}
		else
			return (0);
		str++;
	}
	return (neg * ft_getnum(str));
}
