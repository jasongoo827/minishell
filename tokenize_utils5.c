/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:24:12 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 19:13:55 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	check_nonword_token(t_token_category category)
{
	if (category == T_IN_RE || category == T_OUT_RE)
		return (2);
	if (category == T_HERE_RE || category == T_APPEND_RE)
		return (2);
	if (category == T_AND || category == T_OR)
		return (1);
	if (category == T_PIPE)
		return (1);
	return (0);
}

void	update_error_token(t_token *head)
{
	t_token	*token;

	token = head->next;
	while (token->next != NULL)
	{
		if (check_nonword_token(token->category) == 2)
		{
			if (check_nonword_token(token->next->category))
				token->next->category = T_ERROR;
		}
		token = token->next;
	}
}

void	find_quote_char(char *str, char *c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'')
		{
			*c = '\'';
			return ;
		}
		if (str[i] == '\"')
		{
			*c = '\"';
			return ;
		}
	}
}

void	tokenize_meta_branch(char *str, t_token *head, t_token_category c, \
int *flag)
{
	int	len;

	if (c == T_PIPE || c == T_OUT_RE || c == T_IN_RE)
		len = 1;
	else if (c == T_OR || c == T_APPEND_RE || c == T_HERE_RE)
		len = 2;
	if (*flag == 0)
		tokenize_meta_char(str, head, c);
	else
		tokenize_meta_char_error(str, head, len);
}

void	tokenize_branch(char *input, t_token *head, int *i, int *flag)
{
	if (input[*i] == '&')
		tokenize_and(input + *i, head, i, flag);
	else if (input[*i] == '|')
		tokenize_pipe(input + *i, head, i, flag);
	else if (input[*i] == '<')
		tokenize_in_redir(input + *i, head, i, flag);
	else if (input[*i] == '>')
		tokenize_out_redir(input + *i, head, i, flag);
	else if (input[*i] == '(')
		tokenize_parent(input + *i, head, T_LPARENT);
	else if (input[*i] == ')')
		tokenize_parent(input + *i, head, T_RPARENT);
}

void	print_tokenlist(t_token *head)
{
	t_token	*token;
	char	*token_category[12] = {
		"T_WORD", "T_PIPE", "T_OR", "T_AND",
		"T_IN_RE", "T_OUT_RE", "T_HERE_RE", "T_APPEND_RE",
		"T_LPARENT", "T_RPARENT", "T_ERROR", "T_HEAD"
	};

	token = head->next;
	while (token != NULL)
	{
		printf("%s: content: %s \n", token_category[token->category],
		token->content);
		token = token->next;
	}
}
