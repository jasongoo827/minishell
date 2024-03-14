/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_insert_remove_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:12:12 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 13:29:21 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict_bonus.h"

static int	check_ambiguous(char *value)
{
	char	**split_value;
	int		i;

	if (value == NULL)
		return (0);
	split_value = ft_split(value, ' ');
	null_guard(split_value);
	i = -1;
	while (split_value[++i] != NULL)
	{
		if (i > 0)
		{
			i = -1;
			while (split_value[++i] != NULL)
				free(split_value[i]);
			free(split_value);
			return (1);
		}
	}
	i = -1;
	while (split_value[++i] != NULL)
		free(split_value[i]);
	free(split_value);
	return (0);
}

static int	intsert_sub(t_dict *dic, t_dnode *node, char *value, int check_env)
{
	if (value != NULL)
	{
		node->value = ft_strdup(value);
		null_guard(node->value);
		node->is_ambg = check_ambiguous(node->value);
	}
	node->check_env = check_env;
	dic->env_size += check_env;
	if (dic->head == NULL)
	{
		dic->head = node;
		dic->tail = node;
		return (1);
	}
	dic->tail->next = node;
	node->prev = dic->tail;
	dic->tail = node;
	return (1);
}

int	insert_dict(t_dict *dic, char *key, char *value, int check_env)
{
	t_dnode	*node;

	remove_dic(dic, key);
	node = init_dnode();
	null_guard(node);
	node->key = ft_strdup(key);
	null_guard(node->key);
	if (intsert_sub(dic, node, value, check_env) == 0)
		return (0);
	return (1);
}

void	remove_dic(t_dict *dic, char *key)
{
	t_dnode	*node;

	node = find_dic(dic, key);
	if (node == NULL)
		return ;
	if (node == dic->head)
	{
		dic->head = node->next;
		if (dic->head != NULL)
			dic->head->prev = NULL;
	}
	else
	{
		node->prev->next = node->next;
		if (node != dic->tail)
			node->next->prev = node->prev;
	}
	if (dic->tail == node)
		dic->tail = node->prev;
	free(node->key);
	free(node->value);
	free(node);
}
