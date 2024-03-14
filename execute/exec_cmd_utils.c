/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:14:12 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 20:45:17 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_path(char *path)
{
	int	fd;

	if (path == NULL)
		exit(0);
	fd = open(path, O_RDWR);
	if (fd == -1 && ft_strchr(path, '/') != 0)
	{
		if (errno == 21)
			printf_error(path, DIR_ERR, 126);
		if (access(path, F_OK) == -1 || errno == 21)
			printf_error(path, NOF_ERR, 127);
		if (access(path, X_OK) == -1)
			printf_error(path, PER_ERR, 126);
	}
	if (ft_strchr(path, '/') == 0)
		printf_error(path, CNF_ERR, 127);
	if (fd != -1)
		check_fail(close(fd));
}

int	check_fd(int n, char *path, int in_out, int is_parent)
{
	if (n == -1)
	{
		if (access(path, F_OK) == -1)
			printf_error(path, NOF_ERR, -1);
		else if (opendir(path) != NULL)
			printf_error(path, DIR_ERR, -1);
		else if (in_out == IN_FD && access(path, R_OK) == -1)
			printf_error(path, PER_ERR, -1);
		else if (in_out == OUT_FD && access(path, W_OK) == -1)
			printf_error(path, PER_ERR, -1);
		if (is_parent == 1)
			return (1);
		else
			exit(1);
	}
	return (0);
}

int	check_ambgious(char *path, int is_parent)
{
	if (ft_strchr(path, '$') != 0)
	{
		printf_error(path, AMB_ERR, -1);
		if (is_parent == 1)
			return (1);
		else
			exit(1);
	}
	return (0);
}

void	free_t_d(char **cmd)
{
	int	i;

	i = -1;
	if (cmd == NULL)
		return ;
	while (cmd[++i] != NULL)
		free(cmd[i]);
	free(cmd);
}

void	free_cmdlst(t_cmdlst *lst)
{
	t_cnode	*cur;
	t_cnode	*free_cur;
	int		i;

	i = -1;
	cur = lst->head;
	while (cur != NULL)
	{
		free_t_d((char **)cur->cmd_vec->arr);
		cur->cmd_vec->arr = NULL;
		free_vector(cur->cmd_vec);
		free_t_d((char **)cur->re_vec->arr);
		cur->re_vec->arr = NULL;
		free_vector(cur->re_vec);
		if (lst->dic != cur->old_dic)
			free_dic(cur->old_dic);
		free(cur->path);
		free_cur = cur;
		cur = cur->next;
		free(free_cur);
	}
	free(lst);
}
