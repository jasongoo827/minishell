/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:51:36 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 21:06:30 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

void	print_tree(t_node *root)
{
	int	i;
	char	*tree_category[15] = {
		"TREE_ROOT", "TREE_LIST", "TREE_LPARENT", "TREE_RPARENT",
		"TREE_AND", "TREE_OR", "TREE_PIPELINE", "TREE_CMD",
		"TREE_PIPE", "TREE_SIMPLE_CMD", "TREE_SUBSHELL",
		"TREE_SIMPLE_CMD_ELEMENT", "TREE_WORD", "TREE_RE", "TREE_ERROR"
	};
	t_node	*node;
	// t_cmdlst *lst;

	i = -1;
	while (++i < root->child->size)
	{
		node = (t_node *)root->child->arr[i];
		printf("symbol: %s value: %s\n", tree_category[node->category],
		node->token->content);
		print_tree(node);
	}
}

static void	main_loop(t_token *token_list, t_node *root, t_dict *dic)
{
	t_vector	*all_re_vec;
	char		*input;
	int			re_flag;

	while (1)
	{
		input = readline("minishell> \001\033[s\002");
		if (input == NULL)
			sigterm_handler(dic);
		else if (check_input_content(input) == 0)
			continue ;
		add_history(input);
		tokenize(input, token_list);
		// print_tokenlist(token_list);
		make_tree(root, &(token_list->next));
		print_tree(root);
		all_re_vec = root_re_vec(root, dic, &re_flag);
		if (here_doc(all_re_vec, dic) < 0)
		{
			free_loop(&token_list, &root, &input, &all_re_vec);
			continue ;
		}
		all_re_vec = expansion_vec(all_re_vec, dic, 1);
		change_root_hcontent(root, all_re_vec);
		execute(root, dic, &re_flag);
		free_loop(&token_list, &root, &input, &all_re_vec);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_token		*token_list;
	t_node		*root;
	t_dict		*dic;

	(void)argc;
	(void)argv;
	dic = init_dict();
	set_dict(dic, envp);
	signal_handler();
	rl_signal_event_hook = (rl_hook_func_t *)signal_handler;
	init_struct(&token_list, &root);
	main_loop(token_list, root, dic);
	free_init_struct(token_list, root);
}
