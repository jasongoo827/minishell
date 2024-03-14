/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:14 by mkong             #+#    #+#             */
/*   Updated: 2023/11/10 13:16:43 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	check_f(t_list **f_n, t_list *p_n, void *n_c, void (*del)(void *))
{
	if (p_n)
		return (0);
	(*del)(n_c);
	ft_lstclear(f_n, (*del));
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p_node;
	t_list	*f_node;
	void	*new_content;

	if (lst == 0)
		return (0);
	new_content = (*f)(lst->content);
	p_node = ft_lstnew(new_content);
	if (check_f(&p_node, p_node, new_content, (*del)))
		return (0);
	f_node = p_node;
	while (lst->next)
	{
		lst = lst->next;
		new_content = (*f)(lst->content);
		p_node->next = ft_lstnew(new_content);
		if (check_f(&f_node, p_node->next, new_content, (*del)))
			return (0);
		p_node = p_node->next;
	}
	p_node->next = 0;
	return (f_node);
}
