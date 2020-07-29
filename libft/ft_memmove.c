/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 19:57:10 by bykim             #+#    #+#             */
/*   Updated: 2020/04/19 21:35:26 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;
	size_t			idx;

	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	idx = 0;
	if (!dest && !src)
		return (0);
	if ((long long)dest_ptr > (long long)src_ptr)
	{
		while (n-- > 0)
			*(dest_ptr + n) = *(src_ptr + n);
	}
	else
	{
		idx = 0;
		while (idx++ < n)
			*(dest_ptr++) = *(src_ptr++);
	}
	return (dest);
}
