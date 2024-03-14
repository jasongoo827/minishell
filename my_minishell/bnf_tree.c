/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnf_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:50:28 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:15:49 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "./execute/exec.h"

t_node	*create_node(t_token *token, t_tree_category category)
{
	t_node	*node;
	char	*content;

	node = (t_node *)malloc(sizeof(t_node));
	null_guard((char *)node);
	node->child = init_vector(INIT_SIZE);
	if (token->content == NULL)
		content = NULL;
	else
		content = ft_strdup(token->content);
	node->token = create_token(content, token->category);
	node->category = category;
	return (node);
}

void	add_child(t_node *root, t_node *node)
{
	push_back(root->child, (void *)node);
}

void	make_tree(t_node *root, t_token **lst)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	node = create_node(token, TREE_LIST);
	make_tree_layer1(node, &token);
	add_child(root, node);
}

void	make_tree_layer1(t_node *root, t_token **lst)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	while (token != NULL)
	{
		if (token->category == T_RPARENT)
		{
			*lst = token;
			return ;
		}
		if (token->category == T_AND || token->category == T_OR)
			make_tree_layer1_branch(&node, &token);
		else
		{
			node = create_node(token, TREE_PIPELINE);
			make_tree_layer2(node, &token);
		}
		add_child(root, node);
	}
	*lst = token;
}

void	make_tree_layer2(t_node *root, t_token **lst)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	while (token != NULL)
	{
		if (token->category == T_OR || token->category == T_AND \
		|| token->category == T_RPARENT)
		{
			*lst = token;
			return ;
		}
		if (token->category == T_PIPE)
		{
			node = create_node(token, TREE_PIPE);
			token = token->next;
		}
		else
		{
			node = create_node(token, TREE_CMD);
			make_tree_layer3(node, &token);
		}
		add_child(root, node);
	}
	*lst = token;
}
