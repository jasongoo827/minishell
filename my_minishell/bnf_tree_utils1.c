/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnf_tree_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:50:57 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/05 13:27:46 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

int	check_token_treelist(t_token *token)
{
	if (token->category == T_AND || token->category == T_OR)
		return (0);
	return (1);
}

int	check_tree_nodes(t_node *node)
{
	if (node->category == TREE_AND || node->category == TREE_OR)
		return (0);
	if (node->category == TREE_LPARENT || node->category == TREE_RPARENT)
		return (0);
	if (node->category == TREE_WORD || node->category == TREE_RE)
		return (0);
	return (1);
}

void	iter_token_list(t_token **lst, t_node *root)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	while (check_token_treelist(token))
	{
		node = create_node(token, TREE_LIST);
		add_child(root, node);
		token = token->next;
	}
}

void	free_tree(t_node *root)
{
	t_node	*node;
	int		i;

	i = -1;
	while (++i < root->child->size)
	{
		node = (t_node *)root->child->arr[i];
		free(node->token->content);
		free(node->token);
		free_tree(node);
		free_vector(node->child);
		free(node);
	}
}

void	clean_root_vector(t_node *root)
{
	int	i;

	i = -1;
	while (++i < root->child->size)
		root->child->arr[i] = 0;
	root->child->size = 0;
}
