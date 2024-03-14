/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:57:23 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 13:28:20 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

static	int	check_unset_valid(char *key)
{
	if (ft_isalpha(key[0]) || key[0] == '_')
		return (1);
	ft_putstr_fd("unset: \'", 2);
	ft_putstr_fd(key, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	return (0);
}

int	builtin_unset(t_dict *dic, t_vector *cmd_vec)
{
	int	i;

	i = 0;
	while (++i < cmd_vec->size - 1)
	{
		cmd_vec->arr[i] = change_env(dic, cmd_vec->arr[i], 0);
		if (cmd_vec->arr[i] == NULL)
			return (1);
	}
	i = 0;
	while (++i < cmd_vec->size - 1)
		if (check_unset_valid(cmd_vec->arr[i]) == 1)
			remove_dic(dic, cmd_vec->arr[i]);
	return (0);
}
