/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:48:38 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:30:23 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

t_node	*find_list_node(t_node *node)
{
	t_node	*list;
	int		i;
	int		j;

	i = -1;
	while (++i < node->child->size)
	{
		j = -1;
		list = (t_node *)node->child->arr[i];
		while (++j < list->child->size)
			if (((t_node *)list->child->arr[j])->category == TREE_SUBSHELL)
				return ((t_node *)list->child->arr[j]);
	}
	return (NULL);
}

int	exec_pline(t_node *root, t_node *node, t_dict *dic)
{
	t_cmdlst	*lst;
	int			re_flag;

	if (dic->exec_flag)
		return (1);
	if (!check_pipe(node, dic) || !check_error_node(root, dic) || \
	!check_subshell(node, dic) || !check_after_subshell(node, dic))
		return (-1);
	if (!ft_strncmp(node->token->content, "(", 2))
	{
		re_flag = 0;
		node = find_list_node(node);
		execute(node, dic, &re_flag);
		return (1);
	}
	lst = make_cmdlst(node, dic);
	dic->exit_status = 0;
	g_last_signal = 0;
	exec_cmd(lst, dic);
	free_cmdlst(lst);
	return (1);
}

int	exec_and(t_node *root, t_node *node, t_dict *dic)
{
	if (!check_pipeline(root))
	{
		syntax_error(node->token->content);
		dic->exit_status = 258;
		return (-1);
	}
	if (!dic->exit_status)
	{
		dic->exec_flag = 0;
		return (1);
	}
	else
	{
		dic->exec_flag = 1;
		return (1);
	}
}

int	exec_or(t_node *root, t_node *node, t_dict *dic)
{
	if (!check_pipeline(root))
	{
		syntax_error(node->token->content);
		dic->exit_status = 258;
		return (-1);
	}
	if (!dic->exit_status)
	{
		dic->exec_flag = 1;
		return (1);
	}
	else
	{
		dic->exec_flag = 0;
		return (1);
	}
}

int	check_syntax_error(t_node *node, t_node *scmd, t_dict *dic, int i)
{
	if (node->token->category == T_ERROR)
	{
		syntax_error(node->token->content);
		dic->exit_status = 258;
		return (1);
	}
	if (node->token->category == T_IN_RE || \
	node->token->category == T_OUT_RE || \
	node->token->category == T_APPEND_RE)
	{
		if (scmd->child->size == 1 || i == scmd->child->size - 1)
		{
			syntax_error("newline");
			dic->exit_status = 258;
			return (1);
		}
	}
	return (0);
}
