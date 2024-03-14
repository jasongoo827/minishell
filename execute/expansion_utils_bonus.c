/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:25:39 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 19:23:43 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

static char	*dnode_null(char *e_p, char *e_n)
{
	char	*arg;

	if (e_p == NULL && e_n == NULL)
	{
		arg = (char *)malloc(1);
		null_guard(arg);
		arg[0] = 0;
	}
	else
		arg = ft_strjoin(e_p, e_n);
	null_guard(arg);
	return (arg);
}

static char	*check_dnode_value(t_dnode *node, char *e_p, char *e_n, int *len_i)
{
	char	*tmp;
	char	*env;
	char	*arg;

	if (node == NULL || node->check_env == 0 || node->value == NULL)
	{
		len_i[1]--;
		arg = dnode_null(e_p, e_n);
	}
	else
	{
		env = ft_strdup(node->value);
		null_guard(env);
		tmp = ft_strjoin(e_p, env);
		null_guard(tmp);
		arg = ft_strjoin(tmp, e_n);
		null_guard(arg);
		free(env);
		free(tmp);
	}
	return (arg);
}

static char	*change_env_sub(char *arg, t_dict *dic, int len_i[2], int re)
{
	t_dnode	*node;
	char	*env;
	char	*env_pre;
	char	*env_next;

	null_guard(env = ft_strndup(arg + len_i[1] - len_i[0], len_i[0]));
	node = find_dic(dic, env);
	free(env);
	if (re == 1 && (node == NULL || (node != NULL && node->is_ambg == 1)))
	{
		len_i[1]++;
		return (arg);
	}
	env_pre = ft_strndup(arg, len_i[1] - len_i[0] - 1);
	if (len_i[1] - len_i[0] - 1 != 0)
		null_guard(env_pre);
	env_next = ft_strndup(arg + len_i[1], ft_strlen(arg + len_i[1]));
	if (ft_strlen(arg + len_i[1]) != 0)
		null_guard(env_next);
	free(arg);
	arg = check_dnode_value(node, env_pre, env_next, len_i);
	free(env_pre);
	free(env_next);
	len_i[1] -= len_i[0] + 1;
	return (arg);
}

char	*change_env_normal(t_dict *dic, char *arg, int *i, int re)
{
	int	len_i[2];

	len_i[0] = 0;
	if (arg[*i + 1] == '$')
		return (arg);
	while (*i < (int)ft_strlen(arg) && arg[++(*i)] != 0)
	{
		if (!ft_isalnum(arg[*i]) && arg[*i] != '_')
			break ;
		len_i[0]++;
	}
	if (len_i[0] != 0)
	{
		len_i[1] = *i;
		arg = change_env_sub(arg, dic, len_i, re);
		*i = len_i[1];
	}
	return (arg);
}

char	*change_env_question(t_dict *dic, char *arg, int *i)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		len;

	(*i)++;
	null_guard(tmp1 = ft_substr(arg, 0, *i - 1));
	if (g_last_signal == 1)
	{
		null_guard(tmp2 = ft_strdup("1"));
		g_last_signal = 0;
	}
	else
		null_guard(tmp2 = ft_itoa(dic->exit_status));
	len = ft_strlen(tmp2);
	null_guard(tmp3 = ft_strjoin(tmp1, tmp2));
	free(tmp1);
	null_guard(tmp1 = ft_substr(arg + *i + 1, 0, ft_strlen(arg + *i + 1)));
	free(tmp2);
	null_guard(tmp2 = ft_strjoin(tmp3, tmp1));
	free(tmp1);
	free(tmp3);
	free(arg);
	(*i)--;
	return (tmp2);
}
