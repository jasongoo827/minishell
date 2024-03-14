/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnf_tree_utils3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:06:39 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:32:22 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree_bonus.h"

void	make_tree_subshell_branch(t_node *root, t_node *node, \
t_token **token, t_token **lst)
{
	t_token	*t;

	t = *token;
	add_child(root, node);
	t = t->next;
	*token = t;
	*lst = *token;
}
