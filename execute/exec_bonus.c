/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:30:36 by mkong             #+#    #+#             */
/*   Updated: 2024/03/15 15:45:06 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

static void	exec_pipe_cmd(t_cnode *cnd, pid_t pid)
{
	char	**envp;

	if (pid == 0)
	{
		pipe_handler(cnd);
		re_handler(cnd->re_vec, cnd->old_dic, 0);
		if (cnd->b_category == ELSE)
		{
			check_path(cnd->path);
			envp = make_envp(cnd->old_dic);
			null_guard(envp);
			child_signal_handler();
			if (execve(cnd->path, (char **)cnd->cmd_vec->arr, envp) == -1)
				printf_error(cnd->path, EXE_ERR, 1);
		}
		else
			exit(exec_builtin(cnd, 0, 0));
	}
	if (*cnd->input_fd != -1)
	{
		check_fail(close(*cnd->input_fd));
		check_fail(close(*cnd->output_fd));
	}
	*cnd->output_fd = cnd->fds[1];
	*cnd->input_fd = cnd->fds[0];
}

static pid_t	exec_cnode(t_cmdlst *lst, t_cnode *cnd)
{
	pid_t	pid;
	int		fds[2];

	pid = 0;
	if (lst->size == 1 && cnd->b_category != ELSE)
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
		if (re_handler(cnd->re_vec, cnd->old_dic, 1) == 0)
			lst->dic->exit_status = exec_builtin(cnd, 1, lst->pre_exit_status);
		check_fail(dup2(fds[0], 0));
		check_fail(dup2(fds[1], 1));
		check_fail(close(fds[0]));
		check_fail(close(fds[1]));
	}
	else
	{
		if (cnd->pipe == 1)
			check_fail(pipe(cnd->fds));
		lst->child++;
		pid = fork();
		exec_pipe_cmd(cnd, pid);
	}
	return (pid);
}

void	exec_cmd(t_cmdlst *lst, t_dict *dic)
{
	t_cnode	*cnd;
	pid_t	pid;
	int		i;

	i = -1;
	cnd = lst->head;
	pid = 0;
	while (++i < lst->size && (cnd->cmd_vec->size > 1 || cnd->re_vec->size > 1))
	{
		pid = exec_cnode(lst, cnd);
		cnd = cnd->next;
	}
	signal(SIGINT, SIG_IGN);
	signal_by_exit_status(pid, dic);
	while (--lst->child > 0)
		check_fail(wait(NULL));
	signal_handler();
}

void	execute(t_node *root, t_dict *dic, int *re_flag)
{
	t_node		*node;
	int			i;

	i = -1;
	if (*re_flag)
		return ;
	while (++i < root->child->size)
	{
		node = (t_node *)root->child->arr[i];
		if (node->category == TREE_PIPELINE && exec_pline(root, node, dic) < 0)
			return ;
		else if (node->category == TREE_AND && exec_and(root, node, dic) < 0)
			return ;
		else if (node->category == TREE_OR && exec_or(root, node, dic) < 0)
			return ;
		if (node->category == TREE_PIPELINE
			&& !ft_strncmp(node->token->content, "(", 2))
		{
			if (i == root->child->size - 1)
				return ;
			execute((t_node *)root->child->arr[i + 1], dic, re_flag);
		}
		else
			execute(node, dic, re_flag);
	}
}
