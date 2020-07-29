/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 01:12:56 by bykim             #+#    #+#             */
/*   Updated: 2020/04/19 23:17:24 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbr(long long n, int fd)
{
	long long	remainder;
	char		c;

	if (n == 0)
		return ;
	remainder = n % 10;
	putnbr(n / 10, fd);
	c = '0' + remainder;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	temp;

	temp = n;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (temp < 0)
	{
		temp *= -1;
		write(fd, "-", 1);
	}
	putnbr(temp, fd);
}
