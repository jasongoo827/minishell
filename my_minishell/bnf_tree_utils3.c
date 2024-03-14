/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnf_tree_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:06:39 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/13 16:06:40 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

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
