/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:53:07 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:32:01 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_BONUS_H
# define SIGNAL_BONUS_H

# include "essential_bonus.h"
# include "error_bonus.h"
# include "./dictionary/dict_bonus.h"

# define MSG_SIGQUIT "Quit: 3\n" 
# define MSG_SIGTERM "exit\n"

// signal.c
void	sigint_handler(void);
void	signal_handler(void);
void	init_rl_catch_signals(void);
void	sigterm_handler(t_dict *dic);
void	heredoc_sigterm_handler(void);

// signal_utils.c
void	signal_by_exit_status(pid_t pid, t_dict *dic);
void	heredoc_rl_catch_signals(void);
void	parent_signal_handler(void);
void	child_signal_handler(void);

// signal_utils2.c
int		heredoc_signal_exit_status(void);

#endif
