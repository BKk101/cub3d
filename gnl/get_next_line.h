/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bk <bk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:01:54 by bykim             #+#    #+#             */
/*   Updated: 2020/07/30 16:22:30 by bk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 32

typedef struct	s_buf{
	char		buf[BUFFER_SIZE + 1];
	char		remain[BUFFER_SIZE + 1];
}				t_buf;

int				get_next_line(int fd, char **line);
size_t			ftt_strlen(const char *s);
char			*ftt_strchr(const char *s, int c);
char			*ftt_strdup(const char *src, int byte);
char			*ftt_strjoin(char *s1, char *s2);
void			*ftt_memset(void *s, int c, size_t n);
void			*ftt_memmove(void *dest, const void *src, size_t n);

#endif
