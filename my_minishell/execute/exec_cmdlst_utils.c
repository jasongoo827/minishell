/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdlst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:13:03 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 12:25:46 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	insert_cnode_sub(t_cmdlst *lst, t_cnode *node)
{
	t_cnode	*tmp;

	node->fds = lst->fds;
	node->pipe = 1;
	node->input_fd = &lst->input_fd;
	node->output_fd = &lst->output_fd;
	if (lst->head == NULL)
	{
		lst->head = node;
		lst->tail = node;
	}
	else
	{
		tmp = lst->head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
		lst->tail = node;
	}
	lst->size++;
}

void	insert_cnode(t_cmdlst *lst, t_vector *cmd_vec, t_vector *re_vec)
{
	t_cnode	*node;

	node = init_cnode(lst->dic);
	null_guard(node);
	node->cmd_vec = cmd_vec;
	node->re_vec = re_vec;
	node->b_category = check_builtin(node->cmd_vec->arr[0]);
	node->path = NULL;
	if (node->b_category == ELSE)
		node->path = make_path(node);
	insert_cnode_sub(lst, node);
}

static void	make_cmd_vec_word(char *content, t_vector *c_v, t_vector *r_v)
{
	char	**c_split;
	char	*ret_content;
	int		i;

	i = -1;
	c_split = ms_split(content, ' ');
	null_guard(c_split);
	i = -1;
	while (c_split[++i] != NULL)
	{
		ret_content = ft_strdup(c_split[i]);
		null_guard(ret_content);
		if (r_v->size % 2 == 1)
			push_back(r_v, ret_content);
		else
			push_back(c_v, ret_content);
	}
	free_t_d(c_split);
}

static void	make_cmd_vec_sub(t_node *root, t_vector *c_v, t_vector *r_v)
{
	char	*content;

	content = ft_strdup(root->token->content);
	null_guard(content);
	if (root->category == TREE_RE)
		push_back(r_v, content);
	else if (root->category == TREE_WORD)
	{
		make_cmd_vec_word(content, c_v, r_v);
		free(content);
	}
	else
		free(content);
}

void	make_cmd_vec(t_dict *dic, t_node *root, t_vector *c_v, t_vector *r_v)
{
	t_node	*node;
	int		i;

	i = -1;
	make_cmd_vec_sub(root, c_v, r_v);
	while (++i < root->child->size)
	{
		node = (t_node *)root->child->arr[i];
		make_cmd_vec(dic, node, c_v, r_v);
	}
}
