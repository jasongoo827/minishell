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

static t_node	*get_tmp_addr(t_node *node, t_node *root, int i, int j)
{
	t_node	*ret;

	ret = NULL;
	if (j > 0)
		ret = node->child->arr[j - 1];
	else if (j == 0 && j + 1 < node->child->size)
		ret = node->child->arr[j + 1];
	else if (i == 0 && i + 1 < root->child->size)
		ret = root->child->arr[i + 1];
	else if (i > 0)
		ret = root->child->arr[i - 1];
	return (ret);
}

static int	check_front_back(t_node *root, t_node *node, t_dict *dic, int i)
{
	t_node	*in_node;
	t_node	*tmp;
	int		j;

	j = -1;
	while (++j < node->child->size)
	{
		in_node = node->child->arr[j];
		if (in_node->category == TREE_SUBSHELL)
		{
			tmp = get_tmp_addr(node, root, i, j);
			if (tmp == NULL)
				return (1);
			syntax_error(tmp->token->content);
			dic->exit_status = 258;
			return (0);
		}
	}
	return (1);
}

int	check_after_subshell(t_node *root, t_dict *dic)
{
	t_node	*node;
	t_node	*subshell;
	int		i;

	subshell = find_list_node(root);
	if (subshell == NULL)
		return (1);
	i = -1;
	while (++i < root->child->size)
	{
		node = root->child->arr[i];
		if (node->category == TREE_CMD)
		{
			if (!check_front_back(root, node, dic, i))
				return (0);
		}
	}
	return (1);
}
