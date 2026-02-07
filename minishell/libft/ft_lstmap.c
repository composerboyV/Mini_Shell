/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:01:24 by dukim             #+#    #+#             */
/*   Updated: 2024/03/07 03:19:30 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*init_lst(t_list **lst, void *(*f)(void *))
{
	t_list	*new;

	new = ft_lstnew(f((*lst)->content));
	if (!new)
		return (0);
	*lst = (*lst)->next;
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*ptr;
	t_list	*new;

	if (!lst)
		return (0);
	start = init_lst(&lst, f);
	if (!start)
		return (0);
	ptr = start;
	while (lst != 0)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&start, del);
			return (0);
		}
		ptr->next = new;
		ptr = ptr->next;
		lst = lst->next;
	}
	return (start);
}
