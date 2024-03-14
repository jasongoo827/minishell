/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:44:35 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 13:30:34 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus.h"

char	*make_here_name(void)
{
	char	*tmp_name;
	char	*tmp;
	int		i;

	tmp = ft_strdup("0");
	null_guard(tmp);
	tmp_name = ft_strjoin(".", tmp);
	null_guard(tmp_name);
	free(tmp);
	i = 0;
	while (access(tmp_name, F_OK) == 0)
	{
		free(tmp_name);
		tmp = ft_itoa(++i);
		null_guard(tmp);
		tmp_name = ft_strjoin(".", tmp);
		null_guard(tmp_name);
		free(tmp);
	}
	return (tmp_name);
}

static void	exec_here_doc(char *tmp_name, char *delimeter, t_dict *dic)
{
	char	*s;
	char	*after_deli;
	int		fd;

	fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_fail(fd);
	after_deli = get_after_deli(delimeter);
	while (1)
	{
		signal(SIGINT, SIG_DFL);
		heredoc_rl_catch_signals();
		s = readline("> \001\033[s\002");
		if (s == NULL)
			heredoc_sigterm_handler();
		check_deli(after_deli, s, fd);
		s = change_env(dic, s, 0);
		ft_putendl_fd(s, fd);
		free(s);
	}
	free(after_deli);
	check_fail(close(fd));
	exit(0);
}

int	here_doc(t_vector *re_vec, t_dict *dic)
{
	char	*tmp_name;
	pid_t	pid;
	int		i;

	i = -1;
	count_here_doc(re_vec);
	while (++i < re_vec->size)
	{
		if (ft_strncmp(re_vec->arr[i], "<<", 3) == 0)
		{
			if (check_heredoc_syntax(re_vec, dic, i) < 0)
				return (-1);
			i++;
			tmp_name = make_here_name();
			parent_signal_handler();
			pid = fork();
			if (pid == 0)
				exec_here_doc(tmp_name, re_vec->arr[i], dic);
			heredoc_etc(tmp_name, re_vec, i);
			if (check_heredoc_exit(re_vec, dic, i) < 0)
				return (-1);
		}
	}
	return (1);
}

void	delete_here_doc(t_vector *re_vec)
{
	int	i;

	i = -1;
	if (re_vec == NULL)
		return ;
	while (++i < re_vec->size - 1)
	{
		if (ft_strncmp(re_vec->arr[i], "<<", 3) == 0)
			check_fail(unlink(re_vec->arr[++i]));
	}
}

void	count_here_doc(t_vector *re_vec)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (++i < re_vec->size)
	{
		if (ft_strncmp(re_vec->arr[i], "<<", 3) == 0)
			cnt++;
	}
	if (cnt > 16)
		printf_error(NULL, HER_ERR, 2);
}
