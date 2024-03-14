/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:17:11 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:30:25 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

int	check_subshell(t_node *root, t_dict *dic)
{
	t_node	*node;
	t_node	*subshell;
	int		i;

	i = -1;
	subshell = find_list_node(root);
	if (subshell == NULL)
		return (1);
	while (++i < subshell->child->size)
	{
		node = subshell->child->arr[i];
		if (node->category == TREE_LIST)
			return (1);
	}
	syntax_error(")");
	dic->exit_status = 258;
	return (0);
}

int	check_between_pipe(t_node *root, t_dict *dic, int i)
{
	t_node	*next;

	next = root->child->arr[i + 1];
	if (next->category != TREE_CMD)
	{
		syntax_error("|");
		dic->exit_status = 258;
		return (0);
	}
	return (1);
}
