/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:18 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 19:07:50 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	check_word(char c)
{
	if (c == '\'' || c == '\"')
		return (0);
	return (1);
}

int	check_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && check_word(str[i]))
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_quote_cnt(char *str, char c)
{
	int	len;
	int	i;
	int	cnt;

	len = 0;
	if (!ft_strchr(str, c))
		return (0);
	while (str[len] && check_word(str[len]))
		len++;
	i = -1;
	cnt = 0;
	while (++i < len)
	{
		if (str[i] == c)
			cnt++;
	}
	if (cnt % 2 == 0)
		return (1);
	else
		return (0);
}

void	tokenize_word_branch(char *str, t_token *head, int *idx)
{
	if (str[0] == '\'' || str[0] == '\"')
	{
		tokenize_quote(str, head, idx, str[0]);
		return ;
	}
	else
		tokenize_word(str, head, idx);
}

void	tokenize_quote(char *str, t_token *head, int *idx, char c)
{
	t_token	*token;
	char	*content;
	int		len;

	if (!check_quote_cnt(str, c) || !check_quote_cnt(str, c))
	{
		null_guard(content = ft_substr(str, 0, 1));
		token = create_token(content, T_ERROR);
		add_token(&head, token);
		return ;
	}
	len = 1;
	while (str[len] && str[len] != c)
		len++;
	content = ft_substr(str, 0, ++len);
	null_guard(content);
	token = create_token(content, T_WORD);
	add_token(&head, token);
	*idx += (len - 1);
}
