/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:44 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:33:16 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_bonus.h"

int	check_word_quote_space(char *str, char c)
{
	int		i;
	char	*pos;

	i = 0;
	pos = ft_strchr(str, c);
	while (str != pos)
	{
		if (*str == ' ')
			return (1);
		str++;
	}
	return (0);
}

void	tokenize_word(char *str, t_token *head, int *idx)
{
	t_token	*token;
	char	*content;
	int		len;

	len = 0;
	while (str[len] && check_word(str[len]) && str[len] != ' ')
		len++;
	content = ft_substr(str, 0, len);
	null_guard(content);
	token = create_token(content, T_WORD);
	add_token(&head, token);
	*idx += (len - 1);
}

void	tokenize_word_quote(char *str, t_token *head, int *idx)
{
	t_token	*token;
	char	*content;
	int		len;
	char	c;

	find_quote_char(str, &c);
	if (check_word_quote_space(str, c))
		tokenize_word(str, head, idx);
	else
	{
		len = 0;
		while (str[len] && check_word(str[len]))
			len++;
		content = ft_substr(str, 0, len);
		null_guard(content);
		token = create_token(content, T_WORD);
		add_token(&head, token);
		*idx += (len - 1);
	}
}

void	tokenize_error(char *str, t_token *head, int *idx)
{
	t_token	*token;
	char	*content;
	int		len;

	len = 0;
	while (str[len] && check_word(str[len]) && str[len] != ' ')
		len++;
	content = ft_substr(str, 0, len);
	null_guard(content);
	token = create_token(content, T_ERROR);
	add_token(&head, token);
	*idx += (len - 1);
}

void	update_parent_token(t_token *head)
{
	t_token	*token;
	int		l_cnt;
	int		r_cnt;

	l_cnt = 0;
	r_cnt = 0;
	token = head->next;
	while (token != NULL)
	{
		if (token->category == T_LPARENT)
			l_cnt++;
		else if (token->category == T_RPARENT)
			r_cnt++;
		token = token->next;
	}
	if (l_cnt > r_cnt)
		update_lparent_error(head, r_cnt, l_cnt);
	else if (l_cnt < r_cnt)
		update_rparent_error(head, r_cnt - l_cnt);
}
