/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:53:30 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:32:48 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_bonus.h"

void	heredoc_rl_catch_signals(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 1;
}

void	parent_signal_handler(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signal_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_by_exit_status(pid_t pid, t_dict *dic)
{
	int	param;
	int	status;

	waitpid(pid, &status, 0);
	if (!WIFEXITED(status))
	{
		if (WIFSIGNALED(status))
		{
			param = WTERMSIG(status) + 128;
			if (param == 130)
				ft_putstr_fd("\n", 2);
			else if (param == 131)
				ft_putstr_fd(MSG_SIGQUIT, 2);
		}
		else
			param = WEXITSTATUS(status);
	}
	else
		param = WEXITSTATUS(status);
	if (pid != 0)
		dic->exit_status = param;
}
