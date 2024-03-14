/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:31:07 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 12:30:08 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin(t_cnode *node, int is_parent, int pre_exit)
{
	if (node->b_category == CD)
		return (builtin_cd(node->old_dic, node->cmd_vec));
	if (node->b_category == ECHO)
		return (builtin_echo(node->cmd_vec));
	if (node->b_category == ENV)
		return (builtin_env(node->cmd_vec, node->old_dic));
	if (node->b_category == EXIT)
		return (builtin_exit(node->cmd_vec, is_parent, pre_exit));
	if (node->b_category == EXPORT)
		return (builtin_export(node->old_dic, node->cmd_vec));
	if (node->b_category == PWD)
		return (builtin_pwd(node->old_dic));
	if (node->b_category == UNSET)
		return (builtin_unset(node->old_dic, node->cmd_vec));
	return (1);
}

int	is_whitespace(char c)
{
	if (c == 32 || (9 <= c && c <= 13))
		return (1);
	return (0);
}

void	pipe_handler(t_cnode *node)
{
	if (node->pipe == 1)
	{
		if (*node->input_fd != -1)
		{
			check_fail(dup2(*node->input_fd, 0));
			check_fail(close(*node->input_fd));
			check_fail(close(*node->output_fd));
		}
		check_fail(close(node->fds[0]));
		check_fail(dup2(node->fds[1], 1));
		check_fail(close(node->fds[1]));
	}
	if (*node->input_fd != -1 && node->pipe == 0)
	{
		check_fail(dup2(*node->input_fd, 0));
		check_fail(close(*node->input_fd));
		check_fail(close(node->fds[1]));
	}
}

static int	re_handler_sub(t_vector *r_v, int *i, int *fd, int is_parent)
{
	if (check_ambgious(r_v->arr[*i + 1], is_parent))
		return (1);
	if (ft_strncmp(r_v->arr[*i], "<", 2) == 0)
	{
		fd[0] = open(r_v->arr[++(*i)], O_RDONLY);
		return (check_fd(fd[0], r_v->arr[*i], IN_FD, is_parent));
	}
	else if (ft_strncmp(r_v->arr[*i], ">", 2) == 0)
	{
		fd[1] = open(r_v->arr[++(*i)], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (check_fd(fd[1], r_v->arr[*i], OUT_FD, is_parent));
	}
	else if (ft_strncmp(r_v->arr[*i], ">>", 3) == 0)
	{
		fd[1] = open(r_v->arr[++(*i)], O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (check_fd(fd[1], r_v->arr[*i], OUT_FD, is_parent));
	}
	else if (ft_strncmp(r_v->arr[*i], "<<", 3) == 0)
	{
		fd[0] = open(r_v->arr[++(*i)], O_RDONLY);
		return (check_fd(fd[0], r_v->arr[*i], IN_FD, is_parent));
	}
	return (1);
}

int	re_handler(t_vector *r_v, t_dict *dic, int is_parent)
{
	int	fd[2];
	int	check;
	int	i;

	i = -1;
	check = 0;
	while (++i < r_v->size - 1 && check == 0)
	{
		fd[0] = -1;
		fd[1] = -1;
		check = re_handler_sub(r_v, &i, fd, is_parent);
		if (fd[0] != -1)
		{
			check_fail(dup2(fd[0], 0));
			check_fail(close(fd[0]));
		}
		if (fd[1] != -1)
		{
			check_fail(dup2(fd[1], 1));
			check_fail(close(fd[1]));
		}
		if (check == 1)
			dic->exit_status = 1;
	}
	return (check);
}
