/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:40:33 by mkong             #+#    #+#             */
/*   Updated: 2023/11/08 14:21:52 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (lst == 0)
		return ;
	node = *lst;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	if (new)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
}
