/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:30:11 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 19:24:07 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

t_builtin	check_builtin(char *cmd)
{
	if (cmd == NULL)
		return (ELSE);
	if (!ft_strncmp(cmd, "cd", 3))
		return (CD);
	if (!ft_strncmp(cmd, "echo", 5))
		return (ECHO);
	if (!ft_strncmp(cmd, "env", 4))
		return (ENV);
	if (!ft_strncmp(cmd, "exit", 5))
		return (EXIT);
	if (!ft_strncmp(cmd, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(cmd, "unset", 6))
		return (UNSET);
	return (ELSE);
}

char	*change_env(t_dict *dic, char *arg, int re)
{
	int		i;
	int		double_quot;

	i = -1;
	double_quot = 0;
	while (arg != NULL && i < (int)ft_strlen(arg) && arg[++i] != 0)
	{
		if (i < (int)ft_strlen(arg) && arg[i] == '\"')
			double_quot++;
		if (i < (int)ft_strlen(arg) && double_quot % 2 == 0 && arg[i] == '\'')
		{
			if (ft_strchr(arg + i, '\'') == ft_strrchr(arg + i, '\''))
				break ;
			i = ft_strchr(arg + i + 1, '\'') - arg;
		}
		if (i < (int)ft_strlen(arg) && arg[i] == '$')
		{
			if (arg[i + 1] == '?')
				arg = change_env_question(dic, arg, &i);
			else
				arg = change_env_normal(dic, arg, &i, re);
		}
	}
	return (arg);
}

char	*merge_cmd_vec(t_vector *cmd_vec)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = ft_strdup(cmd_vec->arr[0]);
	null_guard(ret);
	while (++i < cmd_vec->size)
	{
		tmp = ft_strjoin(ret, " ");
		null_guard(tmp);
		free(ret);
		ret = ft_strjoin(tmp, cmd_vec->arr[i]);
		null_guard(ret);
		free(tmp);
	}
	return (ret);
}

void	push_cmd(t_vector *ret_vec, char *cmd)
{
	t_vector	*wc_vec;
	char		*after_cmd;
	int			i;

	if (ft_strchr(cmd, '*') != 0)
	{
		wc_vec = expand_wildcard(cmd);
		if (wc_vec == NULL)
			printf_error(cmd, "Wildcard error", 1);
		i = -1;
		while (++i < wc_vec->size)
		{
			null_guard(after_cmd = ft_strdup(wc_vec->arr[i]));
			free(wc_vec->arr[i]);
			push_back(ret_vec, after_cmd);
		}
		free_vector(wc_vec);
	}
	else
	{
		null_guard(after_cmd = ft_strdup(cmd));
		push_back(ret_vec, after_cmd);
	}
}

t_vector	*expansion_vec(t_vector *cmd_vec, t_dict *dic, int re)
{
	t_vector	*ret_vec;
	char		*merge_cmd;
	char		**split_merge;
	int			i;

	if (cmd_vec->size == 0)
		return (cmd_vec);
	merge_cmd = merge_cmd_vec(cmd_vec);
	merge_cmd = change_env(dic, merge_cmd, re);
	split_merge = ms_split(merge_cmd, ' ');
	free(merge_cmd);
	push_back(cmd_vec, NULL);
	free_t_d((char **)cmd_vec->arr);
	cmd_vec->arr = NULL;
	free_vector(cmd_vec);
	ret_vec = init_vector(INIT_SIZE);
	i = -1;
	while (split_merge[++i] != NULL)
	{
		split_merge[i] = rm_quote(split_merge[i]);
		push_cmd(ret_vec, split_merge[i]);
	}
	free_t_d(split_merge);
	push_back(ret_vec, NULL);
	return (ret_vec);
}
