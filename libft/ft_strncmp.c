/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 20:31:51 by bykim             #+#    #+#             */
/*   Updated: 2020/04/19 23:27:58 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		c1 = *s1;
		c2 = *s2;
		if (c1 != c2)
			return (c1 - c2);
		if ((c1 == c2) && i < n)
		{
			if (c1 == '\0')
				return (0);
			s1++;
			s2++;
			i++;
		}
	}
	return (0);
}
