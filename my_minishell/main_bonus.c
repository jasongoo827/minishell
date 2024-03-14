/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:51:36 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:32:32 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

volatile sig_atomic_t	g_last_signal = 0;

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
		make_tree(root, &(token_list->next));
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
