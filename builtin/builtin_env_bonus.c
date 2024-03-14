/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:19:27 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 19:21:24 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*arr;
	int		idx;

	idx = 0;
	if (n == 0)
		return (NULL);
	arr = (char *)malloc(n + 1);
	null_guard(arr);
	while (n != 0)
	{
		arr[idx] = s1[idx];
		idx++;
		n--;
	}
	arr[idx] = '\0';
	return (arr);
}

char	*remove_twin(char *cmd, char c, int *i)
{
	char	*tmp1;
	char	*tmp2;
	int		cnt;
	int		k;

	cnt = 0;
	k = ft_strchr(cmd + *i + 1, c) - cmd - *i - 1;
	null_guard(tmp1 = ft_substr(cmd, 0, *i));
	null_guard(tmp2 = ft_substr(cmd, *i + 1, ft_strlen(cmd + *i + 1)));
	free(cmd);
	null_guard(cmd = ft_strjoin(tmp1, tmp2));
	free(tmp1);
	free(tmp2);
	null_guard(tmp1 = ft_substr(cmd, 0, ft_strchr(cmd + *i, c) - cmd));
	null_guard(tmp2 = ft_substr(cmd, ft_strchr(cmd + *i, c) - cmd + 1, \
							ft_strlen(ft_strchr(cmd + *i, c) + 1)));
	free(cmd);
	null_guard(cmd = ft_strjoin(tmp1, tmp2));
	free(tmp1);
	free(tmp2);
	*i += k - 1;
	return (cmd);
}

static void	*count_quote(int *count_quote, char *cmd)
{
	int	i;

	count_quote[0] = 0;
	count_quote[1] = 0;
	i = -1;
	while (cmd[++i] != 0)
	{
		if (cmd[i] == '\'' && ft_strchr(cmd + i + 1, '\'') != 0)
		{
			count_quote[0] += 2;
			i = ft_strchr(cmd + i + 1, '\'') - cmd;
		}
		else if (cmd[i] == '\"' && ft_strchr(cmd + i + 1, '\"') != 0)
		{
			count_quote[1] += 2;
			i = ft_strchr(cmd + i + 1, '\"') - cmd;
		}
	}
	return (count_quote);
}

char	*rm_quote(char *cmd)
{
	int		i;
	int		c_q[2];

	count_quote(c_q, cmd);
	i = -1;
	while ((c_q[0] != 0 || c_q[1] != 0)
		&& c_q[0] % 2 == 0 && c_q[1] % 2 == 0 && cmd[++i] != 0)
	{
		if (c_q[0] > 0 && i >= 0 && cmd[i] == '\'')
		{
			cmd = remove_twin(cmd, '\'', &i);
			c_q[0] -= 2;
		}
		else if (c_q[1] > 0 && i >= 0 && cmd[i] == '\"')
		{
			cmd = remove_twin(cmd, '\"', &i);
			c_q[1] -= 2;
		}
	}
	return (cmd);
}

int	builtin_env(t_vector *cmd_vec, t_dict *dic)
{
	char	**envp;
	int		i;

	if (cmd_vec->size > 2)
	{
		ft_putstr_fd("minishell: env : Too many argument.\n", 2);
		return (1);
	}
	envp = make_envp(dic);
	null_guard(envp);
	i = -1;
	while (envp[++i] != NULL)
		ft_putendl_fd(envp[i], 1);
	free_t_d(envp);
	return (0);
}
