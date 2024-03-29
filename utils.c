/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:29:43 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 08:22:28 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	free_dptr(char **start, int len)
{
	int i;

	i = -1;
	if (len == 0)
		return ;
	while (++i < len)
		free(*(start + i));
	free(start);
}

int		ft_max(int a, int b)
{
	return (a > b ? a : b);
}

int		ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int		print_error(char *s)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(s, 2);
	return (-1);
}

void	sort_list(t_list *start, int (*cmp)())
{
	int		done;
	void	*tmp;
	t_list	*cur;

	if (!start)
		return ;
	done = 1;
	while (done)
	{
		done = 0;
		cur = start;
		while (cur->next)
		{
			if (cmp(cur->content, cur->next->content) > 0)
			{
				done = 1;
				tmp = cur->content;
				cur->content = cur->next->content;
				cur->next->content = tmp;
			}
			cur = cur->next;
		}
	}
}
