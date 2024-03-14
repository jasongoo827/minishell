/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdlst_maker_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:18:56 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 13:30:16 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

t_cmdlst	*init_cmdlst(t_dict *dic)
{
	t_cmdlst	*lst;

	lst = malloc(sizeof(t_cmdlst));
	null_guard(lst);
	lst->dic = dic;
	lst->pre_exit_status = dic->exit_status;
	lst->size = 0;
	lst->head = NULL;
	lst->tail = NULL;
	ft_bzero(lst->fds, sizeof(lst->fds));
	return (lst);
}

t_cnode	*init_cnode(t_dict *dic)
{
	t_cnode	*node;

	node = (t_cnode *)malloc(sizeof(t_cnode));
	null_guard(node);
	node->next = NULL;
	node->cmd_vec = NULL;
	node->re_vec = NULL;
	node->old_dic = copy_dic(dic);
	null_guard(node->old_dic);
	node->b_category = 0;
	return (node);
}

static void	make_cmdlst_sub(t_node *root, t_dict *dic, t_cmdlst *lst)
{
	t_vector	*cmd_vec;
	t_vector	*re_vec;
	t_node		*node;
	int			i;

	i = -1;
	while (++i < root->child->size)
	{
		node = (t_node *)root->child->arr[i];
		if (node->category == TREE_CMD)
		{
			cmd_vec = init_vector(INIT_SIZE);
			re_vec = init_vector(INIT_SIZE);
			make_cmd_vec(dic, node, cmd_vec, re_vec);
			re_vec = expansion_vec(re_vec, dic, 1);
			cmd_vec = expansion_vec(cmd_vec, dic, 0);
			insert_cnode(lst, cmd_vec, re_vec);
		}
	}
}

t_cmdlst	*make_cmdlst(t_node *root, t_dict *dic)
{
	t_cmdlst	*lst;

	lst = init_cmdlst(dic);
	make_cmdlst_sub(root, dic, lst);
	lst->tail->pipe = 0;
	lst->input_fd = -1;
	lst->output_fd = -1;
	lst->child = 0;
	if (lst->size == 1)
	{
		free_dic(lst->head->old_dic);
		lst->head->old_dic = lst->dic;
	}
	return (lst);
}
