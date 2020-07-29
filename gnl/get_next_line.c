/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:36:56 by bykim             #+#    #+#             */
/*   Updated: 2020/07/30 02:28:13 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ftt_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int		my_gnl(int fd, char **line, t_buf *list)
{
	char	*str;
	char	*move_pos;
	int		byte;

	byte = 1;
	str = ftt_strjoin(ftt_memset(malloc(1), 0, 1), list[fd].remain);
	ftt_memset(list[fd].remain, 0, BUFFER_SIZE);
	while (ftt_strchr(str, '\n') == 0 && byte > 0)
	{
		byte = read(fd, list[fd].buf, BUFFER_SIZE);
		str = ftt_strjoin(str, list[fd].buf);
		ftt_memset(list[fd].buf, 0, BUFFER_SIZE);
	}
	if (ftt_strchr(str, '\n') != 0)
	{
		*line = ftt_strdup(str, ftt_strchr(str, '\n') - str);
		move_pos = ftt_strchr(str, '\n') + 1;
		ftt_memmove(list[fd].remain, move_pos,
		ftt_strlen(str) - (move_pos - str));
	}
	else
		*line = ftt_strdup(str, ftt_strlen(str));
	free(str);
	return (byte);
}

int		get_next_line(int fd, char **line)
{
	static t_buf	buf_list[2000];
	int				rtn;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
		return (-1);
	rtn = my_gnl(fd, line, buf_list);
	if (rtn == 0)
		return (0);
	else if (rtn == -1)
		return (-1);
	else
		return (1);
}
