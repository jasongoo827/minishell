/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essential_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:49:58 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:31:10 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESSENTIAL_BONUS_H
# define ESSENTIAL_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

volatile sig_atomic_t	g_last_signal;

#endif
