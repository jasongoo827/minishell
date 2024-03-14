/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:53:07 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/05 09:53:08 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "essential.h"
# include "error.h"
# include "./dictionary/dict.h"

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
