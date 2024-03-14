/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:42:39 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 13:30:36 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

static void	make_re_vec(t_node *root, t_vector *all_re_vec, t_vector *err_vec)
{
	char	*content;
	int		i;

	i = -1;
	if (root->category == TREE_RE)
	{
		null_guard(content = ft_strdup(root->token->content));
		push_back(all_re_vec, content);
	}
	if (root->category == TREE_WORD && all_re_vec->size % 2 == 1)
	{
		null_guard(content = ft_strdup(root->token->content));
		push_back(all_re_vec, content);
	}
	if (check_re_content(all_re_vec) && root->category == TREE_ERROR)
	{
		null_guard(content = ft_strdup(root->token->content));
		push_back(all_re_vec, content);
		push_back(err_vec, content);
	}
	while (++i < root->child->size)
		make_re_vec((t_node *)root->child->arr[i], all_re_vec, err_vec);
}

t_vector	*root_re_vec(t_node *root, t_dict *dic, int *re_flag)
{
	t_vector	*all_re_vec;
	t_vector	*err_vec;

	*re_flag = 0;
	dic->exec_flag = 0;
	all_re_vec = init_vector(1);
	err_vec = init_vector(1);
	null_guard(all_re_vec);
	make_re_vec(root, all_re_vec, err_vec);
	if (err_vec->size > 0)
	{
		syntax_error(err_vec->arr[0]);
		*re_flag = 1;
		dic->exit_status = 258;
	}
	free_vector(err_vec);
	return (all_re_vec);
}

static void	ch_root_hc_sub(t_node *r, t_vector *re_v, int *ch, int *idx)
{
	t_node	*node;
	int		i;

	i = -1;
	if (r->category == TREE_RE && ++(*idx))
		if (ft_strncmp(r->token->content, "<<", 3) == 0)
			*ch = 1;
	if (r->category == TREE_WORD && *idx % 2 == 1)
	{
		if (*ch == 1)
		{
			free(r->token->content);
			r->token->content = ft_strdup(re_v->arr[*idx]);
			null_guard(r->token->content);
			ch = 0;
		}
		(*idx)++;
	}
	while (++i < r->child->size)
	{
		node = (t_node *)r->child->arr[i];
		ch_root_hc_sub(node, re_v, ch, idx);
	}
}

void	change_root_hcontent(t_node *root, t_vector *all_re_vec)
{
	int	check;
	int	idx;

	check = 0;
	idx = 0;
	ch_root_hc_sub(root, all_re_vec, &check, &idx);
}

int	check_redirect_syntax(char *content)
{
	if (ft_strncmp(content, "<<", 3) == 0)
		return (-1);
	if (ft_strncmp(content, ">>", 3) == 0)
		return (-1);
	if (ft_strncmp(content, "<", 2) == 0)
		return (-1);
	if (ft_strncmp(content, ">", 2) == 0)
		return (-1);
	if (ft_strncmp(content, "|", 2) == 0)
		return (-1);
	if (ft_strncmp(content, "&&", 3) == 0)
		return (-1);
	if (ft_strncmp(content, "||", 3) == 0)
		return (-1);
	if (ft_strncmp(content, "\'", 2) == 0)
		return (-1);
	if (ft_strncmp(content, "\"", 2) == 0)
		return (-1);
	if (ft_strncmp(content, "&", 2) == 0)
		return (-1);
	return (1);
}
