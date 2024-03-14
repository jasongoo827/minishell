/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:14:30 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/08 15:14:31 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

int	heredoc_signal_exit_status(void)
{
	int	status;

	wait(&status);
	if (!WIFEXITED(status))
	{
		ft_putstr_fd("\n", 1);
		g_last_signal = 1;
		return (-1);
	}
	return (1);
}
