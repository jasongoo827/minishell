/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:50:06 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:16:54 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "essential.h"
# include "error.h"
# include "vector.h"

typedef enum e_tree_category
{
	TREE_ROOT,
	TREE_LIST,
	TREE_LPARENT,
	TREE_RPARENT,
	TREE_AND,
	TREE_OR,
	TREE_PIPELINE,
	TREE_CMD,
	TREE_PIPE,
	TREE_SIMPLE_CMD,
	TREE_SUBSHELL,
	TREE_SIMPLE_CMD_ELEMENT,
	TREE_WORD,
	TREE_RE,
	TREE_ERROR
}	t_tree_category;

typedef struct s_node
{
	t_vector		*child;
	t_token			*token;
	t_tree_category	category;
}	t_node;

// bnf_tree.c
t_node	*create_node(t_token *token, t_tree_category category);
void	add_child(t_node *root, t_node *node);
void	make_tree(t_node *root, t_token **lst);
void	make_tree_layer1(t_node *root, t_token **lst);
void	make_tree_layer2(t_node *root, t_token **lst);

// bnf_tree_utils1.c
int		check_token_treelist(t_token *token);
void	iter_token_list(t_token **lst, t_node *root);
int		check_tree_nodes(t_node *node);
void	free_tree(t_node *root);
void	clean_root_vector(t_node *root);

// bnf_tree_utils2.c
void	make_tree_subshell(t_node *root, t_token **lst);
void	make_tree_layer3(t_node *root, t_token **lst);
void	make_tree_layer4(t_node *root, t_token **lst);
void	make_tree_layer5(t_node *root, t_token **lst);
void	make_tree_layer1_branch(t_node **node, t_token **token);

// bnf_tree_utils3.c
void	make_tree_subshell_branch(t_node *root, t_node *node, \
t_token **token, t_token **lst);

#endif
