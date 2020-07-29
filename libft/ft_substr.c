/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 20:29:36 by bykim             #+#    #+#             */
/*   Updated: 2020/04/20 02:18:10 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	idx;

	if (!s || ft_strlen(s) <= start || !len)
		return (ft_strdup(""));
	if ((res = (char *)malloc(len + 1)) == 0)
		return (0);
	idx = 0;
	while (idx < len && s[start] != 0)
		res[idx++] = s[start++];
	res[idx] = '\0';
	return (res);
}
