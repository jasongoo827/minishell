/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnf_tree_utils2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:51:29 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:32:19 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree_bonus.h"

void	make_tree_subshell(t_node *root, t_token **lst)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	while (token != NULL)
	{
		if (token->category == T_LPARENT)
		{
			node = create_node(token, TREE_LPARENT);
			token = token->next;
		}
		else if (token->category == T_RPARENT)
		{
			node = create_node(token, TREE_RPARENT);
			make_tree_subshell_branch(root, node, &token, lst);
			return ;
		}
		else
		{
			node = create_node(token, TREE_LIST);
			make_tree_layer1(node, &token);
		}
		add_child(root, node);
	}
	*lst = token;
}

void	make_tree_layer3(t_node *root, t_token **lst)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	while (token != NULL)
	{
		if (token->category == T_PIPE || token->category == T_OR || \
		token->category == T_AND || token->category == T_RPARENT)
		{
			*lst = token;
			return ;
		}
		if (token->category == T_LPARENT)
		{
			node = create_node(token, TREE_SUBSHELL);
			make_tree_subshell(node, &token);
		}
		else
		{
			node = create_node(token, TREE_SIMPLE_CMD);
			make_tree_layer4(node, &token);
		}
		add_child(root, node);
	}
	*lst = token;
}

void	make_tree_layer4(t_node *root, t_token **lst)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	while (token != NULL)
	{
		if (token->category == T_PIPE || token->category == T_OR || \
		token->category == T_AND || token->category == T_LPARENT || \
		token->category == T_RPARENT)
		{
			*lst = token;
			return ;
		}
		node = create_node(token, TREE_SIMPLE_CMD_ELEMENT);
		make_tree_layer5(node, &token);
		add_child(root, node);
		token = token->next;
	}
	*lst = token;
}

void	make_tree_layer5(t_node *root, t_token **lst)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	if (token->category == T_WORD)
		node = create_node(token, TREE_WORD);
	else if (token->category == T_IN_RE || token->category == T_OUT_RE || \
	token->category == T_APPEND_RE || token->category == T_HERE_RE)
		node = create_node(token, TREE_RE);
	else
		node = create_node(token, TREE_ERROR);
	add_child(root, node);
}

void	make_tree_layer1_branch(t_node **node, t_token **token)
{
	t_node	*tmp_node;
	t_token	*tmp_token;

	tmp_token = *token;
	if (tmp_token->category == T_AND)
	{
		tmp_node = create_node(*token, TREE_AND);
		*node = tmp_node;
		tmp_token = tmp_token->next;
		*token = tmp_token;
	}
	else if (tmp_token->category == T_OR)
	{
		tmp_node = create_node(*token, TREE_OR);
		*node = tmp_node;
		tmp_token = tmp_token->next;
		*token = tmp_token;
	}
}
