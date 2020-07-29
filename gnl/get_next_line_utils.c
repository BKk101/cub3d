/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:04:53 by bykim             #+#    #+#             */
/*   Updated: 2020/07/30 02:50:34 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ftt_strchr(const char *s, int c)
{
	char *ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	if (c == 0)
		return (ptr);
	return (0);
}

char	*ftt_strdup(const char *src, int len)
{
	char *ptr;

	if ((ptr = (char *)malloc(len + 1)) == 0)
		return (0);
	ptr[len] = 0;
	while (--len >= 0)
		ptr[len] = src[len];
	return (ptr);
}

char	*ftt_strjoin(char *s1, char *s2)
{
	char	*temp;
	char	*res;
	int		len;
	int		num;

	len = 0;
	while (s1[len])
		len++;
	num = 0;
	while (s2[num++])
		len++;
	if ((res = (char *)malloc(len + 1)) == 0)
		return (0);
	temp = res;
	num = 0;
	while (s1[num] != '\0')
		*temp++ = s1[num++];
	while (*s2 != '\0')
		*temp++ = *s2++;
	*temp = 0;
	free(s1);
	return (res);
}

void	*ftt_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;
	unsigned long	idx;

	temp = (unsigned char *)s;
	idx = 0;
	while (idx < n)
		temp[idx++] = (unsigned char)c;
	return (s);
}

void	*ftt_memmove(void *dest, const void *src, size_t n)
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
