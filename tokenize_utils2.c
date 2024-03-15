/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:18 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/15 14:38:58 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	check_word(char c)
{
	if (c == '\'' || c == '\"')
		return (0);
	return (1);
}

int	check_quote_cnt(char *str, char c)
{
	int	len;
	int	i;
	int	cnt;

	len = 0;
	if (!ft_strchr(str, c))
		return (0);
	while (str[len])
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
	char	*ret;
	char	*quote_str;
	int		len;

	len = 0;
	quote_str = NULL;
	while (str[len] && !check_meta_char(str[len]))
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			if (!check_quote_cnt(str, str[len]))
			{
				tokenize_error(str, head, idx, len + 1);
				return ;
			}
			else
			{
				quote_str = tokenize_quote(str + len, str[len]);
				break ;
			}
		}
		len++;
	}
	null_guard(ret = ft_substr(str, 0, len));
	tokenize_word(ret, quote_str, head, idx);
}

char	*tokenize_quote(char *str, char c)
{
	char	*content;
	int		len;
	int		in_quote;

	len = 0;
	in_quote = 0;
	while (str[len])
	{
		if (str[len] == c)
			in_quote = !in_quote;
		else if (!in_quote && check_meta_char(str[len]))
			break ;
		len++;
	}
	null_guard(content = ft_substr(str, 0, len));
	return (content);
}
