/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:48:34 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 19:21:45 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

static void	only_export(t_dict *dic)
{
	t_dnode	*cur;

	cur = dic->head;
	while (cur != NULL)
	{
		ft_putstr_fd("delcare -x ", 1);
		ft_putstr_fd(cur->key, 1);
		if (cur->check_env == 1)
		{
			if (cur->value == NULL)
				ft_putstr_fd("=\"\"", 1);
			else
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(cur->value, 1);
				ft_putstr_fd("\"", 1);
			}
		}
		ft_putstr_fd("\n", 1);
		cur = cur->next;
	}
}

static	int	check_export_valid(char *key, char *value, char *equal)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		check = 1;
	while ((int)ft_strlen(key) > 1 && key[++i] != 0)
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			check = 1;
	if (check == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("export: \'", 2);
		ft_putstr_fd(key, 2);
		if (equal != NULL)
			ft_putstr_fd("=", 2);
		if (value != NULL)
			ft_putstr_fd(value, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		return (0);
	}
	return (1);
}

static char	*set_key(t_dict *dic, char *arg)
{
	t_dnode	*node;
	char	*key;

	if (arg[0] == '$')
	{
		key = get_key(&arg[1]);
		node = find_dic(dic, key);
		if (node == NULL)
		{
			free(key);
			null_guard(key = (char *)malloc(sizeof(char)));
			key[0] = 0;
		}
		else
			key = node->value;
	}
	else
		key = get_key(arg);
	return (key);
}

static int	export_key_value(t_dict *old_dic, t_dict *dic, char *arg)
{
	char	*key;
	char	*value;
	int		check;

	key = set_key(old_dic, arg);
	value = get_value(arg);
	if (key == NULL)
		return (0);
	if (check_export_valid(key, value, ft_strchr(arg, '=')) == 0)
	{
		free(key);
		free(value);
		return (0);
	}
	if (ft_strchr(arg, '=') == 0)
		check = insert_dict(dic, key, value, 0);
	else
		check = insert_dict(dic, key, value, 1);
	free(key);
	free(value);
	return (check);
}

int	builtin_export(t_dict *dic, t_vector *cmd_vec)
{
	t_dict	*old_dic;
	int		flag;
	int		i;

	if (cmd_vec->size == 2)
	{
		only_export(dic);
		return (0);
	}
	old_dic = copy_dic(dic);
	if (old_dic == NULL)
		return (1);
	i = 0;
	flag = 0;
	while (++i < cmd_vec->size - 1)
		if (export_key_value(old_dic, dic, cmd_vec->arr[i]) == 0)
			flag = 1;
	free_dic(old_dic);
	return (flag);
}
