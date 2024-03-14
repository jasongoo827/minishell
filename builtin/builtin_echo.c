/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:04:09 by mkong             #+#    #+#             */
/*   Updated: 2024/03/07 17:14:44 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_n_option(char *s)
{
	if (s == NULL || *s++ != '-')
		return (0);
	if (*s == 0)
		return (0);
	while (*s != 0)
		if (*s++ != 'n')
			return (0);
	return (1);
}

static void	echo_str(t_vector *cmd_vec, int i)
{
	if (i == 1)
	{
		if (i == cmd_vec->size - 1)
			return (ft_putstr_fd("\n", 1));
		while (i < cmd_vec->size - 2)
		{
			ft_putstr_fd(cmd_vec->arr[i++], 1);
			ft_putstr_fd(" ", 1);
		}
		ft_putendl_fd(cmd_vec->arr[i], 1);
	}
	else
	{
		if (i == cmd_vec->size - 1)
			return ;
		while (i < cmd_vec->size - 2)
		{
			ft_putstr_fd(cmd_vec->arr[i++], 1);
			ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd(cmd_vec->arr[i], 1);
	}
}

int	builtin_echo(t_vector *cmd_vec)
{
	int	i;

	if (cmd_vec->size - 1 == 1)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	i = 1;
	while (i < cmd_vec->size - 1 && check_n_option(cmd_vec->arr[i]))
		i++;
	while (check_n_option(cmd_vec->arr[i]))
		i++;
	echo_str(cmd_vec, i);
	return (0);
}
