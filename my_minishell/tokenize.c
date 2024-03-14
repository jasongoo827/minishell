/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:51:07 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:16:16 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*create_token(char *content, t_token_category category)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	null_guard(token);
	if (content == NULL)
		token->content = NULL;
	else
		token->content = content;
	token->next = NULL;
	token->category = category;
	return (token);
}

void	add_token(t_token **head, t_token *token)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = token;
}

void	tokenize(char *input, t_token *head)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (input[++i] != '\0')
	{
		while (input[i] != '\0' && check_blank(input[i]))
			i++;
		if ((size_t)i >= ft_strlen(input))
			break ;
		if (input[i] == '&' || input[i] == '|' || input[i] == '<' || \
		input[i] == '>' || input[i] == '(' || input[i] == ')')
			tokenize_branch(input, head, &i, &flag);
		else
			tokenize_word_branch(input + i, head, &i);
	}
	update_parent_token(head);
	update_error_token(head);
}

void	free_tokenlist(t_token *head)
{
	t_token	*token;
	t_token	*d_token;

	token = head->next;
	while (token != NULL)
	{
		d_token = token;
		token = token->next;
		free(d_token->content);
		free(d_token);
	}
	head->next = NULL;
}

int	check_blank(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
