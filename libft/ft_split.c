/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 20:31:19 by bykim             #+#    #+#             */
/*   Updated: 2020/04/19 20:35:07 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_dptr(char **start, char **end)
{
	while (start < end)
		free(*(start++));
}

static void		ftt_strncpy(char *dest, char *start, char *end)
{
	while (start < end)
		*(dest++) = *(start++);
	*dest = '\0';
}

static char		**ft_split_word(char const *s, char c, char **des)
{
	char	**res;
	char	*temp;

	res = des;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		temp = (char *)s;
		while (*s != c && *s != '\0')
			s++;
		if ((*des = (char *)malloc(s - temp + 1)) == 0)
		{
			free_dptr(res, des);
			return (0);
		}
		ftt_strncpy(*(des++), temp, (char *)s);
	}
	*des = 0;
	return (res);
}

char			**ft_split(char const *s, char c)
{
	char		**res;
	char		**temp;
	long long	len;
	long long	word;

	word = 0;
	len = 0;
	while (s[len])
	{
		while (s[len] == c)
			len++;
		if (s[len] == '\0')
			break ;
		while (s[len] != c && s[len] != '\0')
			len++;
		word++;
	}
	if ((temp = (char **)malloc(sizeof(char *) * (word + 1))) == 0)
		return (0);
	if ((res = ft_split_word(s, c, temp)) == 0)
		free(temp);
	return (res);
}
