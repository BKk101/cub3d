/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 20:30:04 by bykim             #+#    #+#             */
/*   Updated: 2020/04/19 20:34:24 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_instr(const char *str, const char *to_find, size_t len, size_t i)
{
	if (*to_find == '\0')
		return (1);
	if ((*str == *to_find) && *str != '\0' && i < len)
		return (is_instr(str + 1, to_find + 1, len, i + 1));
	else
		return (0);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*rtn;

	rtn = (char *)big;
	i = 0;
	if (*little == '\0')
		return (rtn);
	while (rtn[i] != '\0' && i < len)
	{
		if (is_instr(&rtn[i], little, len, i))
			return (&rtn[i]);
		i++;
	}
	return (0);
}
