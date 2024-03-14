/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils4_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:53:15 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:33:18 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_bonus.h"

void	tokenize_meta_char(char *str, t_token *head, \
t_token_category category)
{
	t_token	*token;
	char	*content;
	int		len;

	if (category == T_AND || category == T_OR || category == T_APPEND_RE || \
	category == T_HERE_RE)
		len = 2;
	else
		len = 1;
	content = ft_substr(str, 0, len);
	null_guard(content);
	token = create_token(content, category);
	add_token(&head, token);
}

void	tokenize_meta_char_error(char *str, t_token *head, int len)
{
	t_token	*token;
	char	*content;

	content = ft_substr(str, 0, len);
	null_guard(content);
	token = create_token(content, T_ERROR);
	add_token(&head, token);
}

int	move_idx(char *str, int *idx, int *flag, char c)
{
	int	i;

	i = 0;
	while (str[i] == c)
		i++;
	if (*flag == 0)
		*idx += (i - 1);
	return (i);
}

void	update_lparent_error(t_token *head, int cnt, int p_cnt)
{
	t_token	*token;
	int		i;

	i = 0;
	token = head->next;
	while (token != NULL)
	{
		if (token->category == T_LPARENT)
		{
			if (i == cnt)
			{
				while (token != NULL && i++ != p_cnt)
				{
					if (token->category == T_LPARENT)
						token->category = T_ERROR;
					token = token->next;
				}
				return ;
			}
			i++;
		}
		token = token->next;
	}
}

void	update_rparent_error(t_token *head, int cnt)
{
	t_token	*token;
	int		i;

	i = 0;
	token = head->next;
	while (token != NULL)
	{
		if (token->category == T_RPARENT)
		{
			while (token != NULL && i++ != cnt)
			{
				if (token->category == T_RPARENT)
					token->category = T_ERROR;
				token = token->next;
			}
			return ;
		}
		token = token->next;
	}
}
