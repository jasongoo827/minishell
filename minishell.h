/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:10 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/08 18:55:17 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "essential.h"
# include "token.h"
# include "tree.h"
# include "error.h"
# include "signal.h"
# include "./dictionary/dict.h"
# include "./builtin/builtin.h"
# include "./execute/exec.h"

// utils.c
int		check_input_content(char *input);
void	init_struct(t_token	**token_list, t_node **root);
void	free_struct(t_token	**token_list, t_node **root, char **input);
void	free_init_struct(t_token *token_list, t_node *root);
void	free_loop(t_token	**token_list, t_node **root, char **input, \
t_vector **all_re_vec);

#endif
