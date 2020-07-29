/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 22:10:22 by bykim             #+#    #+#             */
/*   Updated: 2020/04/13 23:28:15 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long long	temp;
	size_t		len;
	char		*res;

	len = 1;
	temp = n;
	if (n < 0)
		temp *= -1;
	if (n < 0)
		len++;
	while ((temp /= 10) > 0)
		len++;
	if ((res = (char *)malloc(len + 1)) == 0)
		return (0);
	if (n < 0)
		res[0] = '-';
	if (n == 0)
		res[0] = '0';
	temp = (long long)n * 10;
	if (n < 0)
		temp *= -1;
	res[len] = '\0';
	while ((temp /= 10) > 0)
		res[--len] = temp % 10 + '0';
	return (res);
}
