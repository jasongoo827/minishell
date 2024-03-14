/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:10 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:31:44 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "essential_bonus.h"
# include "token_bonus.h"
# include "tree_bonus.h"
# include "error_bonus.h"
# include "signal_bonus.h"
# include "./dictionary/dict_bonus.h"
# include "./builtin/builtin_bonus.h"
# include "./execute/exec_bonus.h"

// utils.c
int		check_input_content(char *input);
void	init_struct(t_token	**token_list, t_node **root);
void	free_struct(t_token	**token_list, t_node **root, char **input);
void	free_init_struct(t_token *token_list, t_node *root);
void	free_loop(t_token	**token_list, t_node **root, char **input, \
t_vector **all_re_vec);

#endif
