/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:35 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/11 20:36:34 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"

void	sigint_handler(void)
{
	g_last_signal = 1;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigterm_handler(t_dict *dic)
{
	ft_putstr_fd("\033[u", 2);
	ft_putstr_fd("\033[1B", 2);
	ft_putstr_fd("\033[1A", 2);
	ft_putstr_fd(MSG_SIGTERM, 2);
	if (g_last_signal == 1)
		exit(g_last_signal);
	else
		exit(dic->exit_status);
}

void	signal_handler(void)
{
	init_rl_catch_signals();
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_rl_catch_signals(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
}

void	heredoc_sigterm_handler(void)
{
	ft_putstr_fd("\033[u", 1);
	ft_putstr_fd("\033[1B", 1);
	ft_putstr_fd("\033[1A", 1);
	exit(0);
}
