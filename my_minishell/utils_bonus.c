/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:50:18 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:33:39 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	check_input_content(char *input)
{
	int	i;

	i = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (ft_strlen(input + i) != 0)
		return (1);
	free(input);
	return (0);
}

void	init_struct(t_token	**token_list, t_node **root)
{
	*token_list = create_token(NULL, T_HEAD);
	*root = create_node(*token_list, TREE_ROOT);
}

void	free_struct(t_token	**token_list, t_node **root, char **input)
{
	free_tokenlist(*token_list);
	free_tree(*root);
	clean_root_vector(*root);
	free(*input);
}

void	free_init_struct(t_token *token_list, t_node *root)
{
	clean_root_vector(root);
	free_vector(root->child);
	free(root->token->content);
	free(root->token);
	free(root);
	free(token_list->content);
	free(token_list);
}

void	free_loop(t_token **token_list, t_node **root, char **input, \
t_vector **all_re_vec)
{
	free_struct(token_list, root, input);
	delete_here_doc(*all_re_vec);
	push_back((*all_re_vec), NULL);
	free_t_d((char **)(*all_re_vec)->arr);
	(*all_re_vec)->arr = NULL;
	free_vector(*all_re_vec);
}
