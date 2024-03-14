/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:48:21 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/12 13:53:44 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_pipeline(t_node *root)
{
	t_node	*node;
	int		i;

	i = -1;
	while (++i < root->child->size)
	{
		node = root->child->arr[i];
		if (i == 0 && node->category != TREE_PIPELINE)
			return (0);
	}
	return (1);
}

int	check_pipe(t_node *root, t_dict *dic)
{
	t_node	*node;
	int		i;

	i = -1;
	while (++i < root->child->size)
	{
		node = root->child->arr[i];
		if (node->category == TREE_PIPE)
		{
			if (i == 0 || i == root->child->size - 1)
			{
				if (node->category == TREE_PIPE)
					syntax_error("|");
				dic->exit_status = 258;
				return (0);
			}
			else
			{
				if (!check_between_pipe(root, dic, i))
					return (0);
			}
		}
	}
	return (1);
}

static void	traverse_until_scmd(t_node *root, t_node **scmd)
{
	t_node	*node;
	int		i;

	i = -1;
	while (++i < root->child->size)
	{
		node = root->child->arr[i];
		if (node->category == TREE_SIMPLE_CMD)
		{
			*scmd = node;
			return ;
		}
		traverse_until_scmd(node, scmd);
	}
}

int	check_error_node(t_node *root, t_dict *dic)
{
	t_node	*node;
	t_node	*scmd;
	int		i;

	scmd = NULL;
	traverse_until_scmd(root, &scmd);
	if (scmd == NULL)
		return (1);
	i = -1;
	while (++i < scmd->child->size)
	{
		node = scmd->child->arr[i];
		if (check_syntax_error(node, scmd, dic, i))
			return (0);
	}
	return (1);
}

int	check_re_content(t_vector *vector)
{
	if (vector->size == 0)
		return (0);
	if (ft_strncmp(vector->arr[vector->size - 1], ">>", 3) == 0)
		return (1);
	if (ft_strncmp(vector->arr[vector->size - 1], "<<", 3) == 0)
		return (1);
	if (ft_strncmp(vector->arr[vector->size - 1], ">", 2) == 0)
		return (1);
	if (ft_strncmp(vector->arr[vector->size - 1], "<", 2) == 0)
		return (1);
	return (0);
}
