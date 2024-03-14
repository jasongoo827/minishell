/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:13:23 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 19:23:10 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

static char	*join_path(char *cmd, t_dict *dic)
{
	char	**path;
	char	*path_cmd;
	char	*check_cmd;
	int		i;

	i = -1;
	path_cmd = ft_strjoin("/", cmd);
	path = find_path(dic);
	while (path != NULL && path[++i] != NULL)
	{
		check_cmd = ft_strjoin(path[i], path_cmd);
		null_guard(check_cmd);
		if (access(check_cmd, F_OK) == 0)
		{
			free(path_cmd);
			free_t_d(path);
			return (check_cmd);
		}
		free(check_cmd);
	}
	check_cmd = ft_strdup(cmd);
	null_guard(check_cmd);
	free_t_d(path);
	free(path_cmd);
	return (check_cmd);
}

char	*make_path(t_cnode *node)
{
	char	*check_cmd;
	char	*cmd;

	cmd = node->cmd_vec->arr[0];
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		check_cmd = ft_strdup(cmd);
		null_guard(check_cmd);
		return (check_cmd);
	}
	if (cmd[0] == 0 || !ft_strncmp(cmd, ".", 2) || !ft_strncmp(cmd, "..", 3))
	{	
		null_guard(check_cmd = ft_strdup(cmd));
		return (check_cmd);
	}
	check_cmd = join_path(cmd, node->old_dic);
	return (check_cmd);
}

char	**find_path(t_dict *dic)
{
	char	**path;
	t_dnode	*node;

	path = NULL;
	node = find_dic(dic, "PATH");
	if (node == NULL)
		return (NULL);
	path = ft_split(node->value, ':');
	null_guard(path);
	return (path);
}
