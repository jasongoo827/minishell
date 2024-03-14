/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_make_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:32:16 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 12:11:03 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

t_dict	*init_dict(void)
{
	t_dict	*dic;

	dic = (t_dict *)malloc(sizeof(t_dict));
	null_guard(dic);
	dic->head = NULL;
	dic->tail = NULL;
	dic->env_size = 0;
	dic->exit_status = 0;
	dic->exec_flag = 0;
	return (dic);
}

t_dnode	*init_dnode(void)
{
	t_dnode	*node;

	node = (t_dnode *)malloc(sizeof(t_dnode));
	null_guard(node);
	node->prev = NULL;
	node->next = NULL;
	node->key = NULL;
	node->value = NULL;
	node->check_env = 0;
	node->is_ambg = 0;
	return (node);
}

t_dnode	*find_dic(t_dict *dic, char *key)
{
	t_dnode	*cur;

	cur = dic->head;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_dict	*copy_dic(t_dict *dic)
{
	t_dict	*cp_dic;
	t_dnode	*node;

	cp_dic = init_dict();
	null_guard(cp_dic);
	cp_dic->env_size = dic->env_size;
	cp_dic->exec_flag = dic->exec_flag;
	cp_dic->exit_status = dic->exit_status;
	node = dic->head;
	while (node != NULL)
	{
		if (!insert_dict(cp_dic, node->key, node->value, node->check_env))
			return (NULL);
		node = node->next;
	}
	return (cp_dic);
}

void	free_dic(t_dict *dic)
{
	t_dnode	*node;

	node = dic->head;
	while (node != NULL)
	{
		dic->head = dic->head->next;
		free(node->key);
		free(node->value);
		free(node);
		node = dic->head;
	}
	dic->tail = NULL;
	free(dic);
}
