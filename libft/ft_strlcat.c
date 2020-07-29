/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:52:29 by bykim             #+#    #+#             */
/*   Updated: 2020/04/20 11:57:48 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	i = 0;
	dlen = 0;
	slen = 0;
	while (dest[i] != '\0' && i < size)
	{
		i++;
		dlen++;
	}
	while (src[slen] != '\0')
		slen++;
	while (*src != '\0' && i + 1 < size)
	{
		dest[i] = *src++;
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	if (size > dlen)
		return (dlen + slen);
	else
		return (size + slen);
}
