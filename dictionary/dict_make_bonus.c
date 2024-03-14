/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_make_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:45:49 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 19:22:13 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict_bonus.h"

char	*get_key(char *env)
{
	char	*key;

	if (ft_strchr(env, '=') == 0)
	{
		key = ft_strdup(env);
		null_guard(key);
	}
	else
	{
		key = ft_substr(env, 0, ft_strchr(env, '=') - env);
		null_guard(key);
	}
	return (key);
}

char	*get_value(char *env)
{
	char	*value;

	value = NULL;
	if (ft_strchr(env, '=') == 0)
		return (value);
	if (*(ft_strchr(env, '=') + 1) != 0)
	{
		value = ft_strdup(ft_strchr(env, '=') + 1);
		null_guard(value);
	}
	return (value);
}

int	set_dict(t_dict *dic, char **envp)
{
	char	*key;
	char	*value;
	int		i;
	int		check;

	i = -1;
	while (envp[++i] != NULL)
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (ft_strchr(envp[i], '=') == 0)
			check = insert_dict(dic, key, value, 0);
		else
			check = insert_dict(dic, key, value, 1);
		free(key);
		free(value);
		if (check == 0)
			return (0);
	}
	if (insert_dict(dic, "OLDPWD", 0, 0) == 0)
		return (0);
	return (1);
}

char	*join_key_value(char *key, char *value)
{
	char	*path;
	char	*env;

	path = ft_strjoin(key, "=\0");
	null_guard(path);
	if (value == NULL)
		return (path);
	env = ft_strjoin(path, value);
	if (env == NULL)
		return (NULL);
	free(path);
	return (env);
}

char	**make_envp(t_dict *dic)
{
	char	**envp;
	t_dnode	*cur;
	int		i;

	envp = (char **)malloc(sizeof(char *) * (dic->env_size + 1));
	null_guard(envp);
	cur = dic->head;
	i = -1;
	while (cur != NULL)
	{
		if (cur->check_env == 1)
		{
			envp[++i] = join_key_value(cur->key, cur->value);
			null_guard(envp[i]);
		}
		cur = cur->next;
	}
	envp[++i] = NULL;
	return (envp);
}
