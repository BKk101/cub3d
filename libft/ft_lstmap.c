/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:30:22 by bykim             #+#    #+#             */
/*   Updated: 2020/04/13 23:30:08 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*start;

	start = 0;
	while (lst)
	{
		if ((temp = (t_list *)malloc(sizeof(t_list))) == 0)
		{
			ft_lstclear(&start, del);
			return (0);
		}
		temp->content = f(lst->content);
		temp->next = 0;
		ft_lstadd_back(&start, temp);
		lst = lst->next;
	}
	return (start);
}
