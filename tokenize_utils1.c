/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:51:51 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/05 09:51:53 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	tokenize_and(char *str, t_token *head, int *idx, int *flag)
{
	int	i;

	i = move_idx(str, idx, flag, '&');
	if (i == 1)
		tokenize_meta_char(str, head, T_ERROR);
	else if (i == 2)
	{
		if (*flag == 0)
			tokenize_meta_char(str, head, T_AND);
		else
			tokenize_meta_char_error(str, head, 2);
	}
	else
	{
		if (*flag == 0)
			tokenize_meta_char(str, head, T_AND);
		else
			tokenize_meta_char_error(str, head, 2);
		*flag = 1;
		tokenize_and(str + 2, head, idx, flag);
	}
	*flag = 0;
}

void	tokenize_pipe(char *str, t_token *head, int *idx, int *flag)
{
	int	i;

	i = move_idx(str, idx, flag, '|');
	if (i == 1)
		tokenize_meta_branch(str, head, T_PIPE, flag);
	else if (i == 2)
		tokenize_meta_branch(str, head, T_OR, flag);
	else
	{
		if (*flag == 0)
			tokenize_meta_char(str, head, T_OR);
		else
			tokenize_meta_char_error(str, head, 2);
		*flag = 1;
		tokenize_pipe(str + 2, head, idx, flag);
	}
	*flag = 0;
}

void	tokenize_out_redir(char *str, t_token *head, int *idx, int *flag)
{
	int	i;

	i = move_idx(str, idx, flag, '>');
	if (i == 1)
		tokenize_meta_branch(str, head, T_OUT_RE, flag);
	else if (i == 2)
		tokenize_meta_branch(str, head, T_APPEND_RE, flag);
	else
	{
		if (*flag == 0)
			tokenize_meta_char(str, head, T_APPEND_RE);
		else
			tokenize_meta_char_error(str, head, 2);
		*flag = 1;
		tokenize_out_redir(str + 2, head, idx, flag);
	}
	*flag = 0;
}

void	tokenize_in_redir(char *str, t_token *head, int *idx, int *flag)
{
	int	i;

	i = move_idx(str, idx, flag, '<');
	if (i == 1)
		tokenize_meta_branch(str, head, T_IN_RE, flag);
	else if (i == 2)
		tokenize_meta_branch(str, head, T_HERE_RE, flag);
	else
	{
		if (*flag == 0)
			tokenize_meta_char(str, head, T_HERE_RE);
		else
			tokenize_meta_char_error(str, head, 2);
		*flag = 1;
		tokenize_in_redir(str + 2, head, idx, flag);
	}
	*flag = 0;
}

void	tokenize_parent(char *str, t_token *head, t_token_category category)
{
	t_token	*token;
	char	*content;

	content = ft_substr(str, 0, 1);
	null_guard(content);
	token = create_token(content, category);
	add_token(&head, token);
}
