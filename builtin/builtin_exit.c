/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:44:34 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 12:32:09 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	exit_err_exit(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static long long	ft_atoll(char *str)
{
	long long		ret;
	int				sign;
	int				i;

	ret = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (str[i] == 0 || ft_strlen(str + i) > 19)
		exit_err_exit(str);
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			exit_err_exit(str);
		ret = 10 * ret + (str[i] - '0') * sign;
		if (ret == (long long)-922337203685477580 && *(str + i + 1) > '8')
			exit_err_exit(str);
		if (ret == (long long)922337203685477580 && *(str + i + 1) > '7')
			exit_err_exit(str);
		i++;
	}
	return (ret);
}

int	builtin_exit(t_vector *cmd_vec, int is_parent, int pre_exit)
{
	unsigned char	exit_code;

	if (is_parent == 1)
		ft_putstr_fd("exit\n", 1);
	if (cmd_vec->size == 2
		|| (cmd_vec->size == 3 && ft_strncmp(cmd_vec->arr[1], "0", 2) == 0))
		exit(pre_exit);
	exit_code = ft_atoll(cmd_vec->arr[1]);
	if (cmd_vec->size > 3)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit(exit_code);
	return (0);
}
