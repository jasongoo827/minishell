/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:49:33 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 11:33:15 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	return (pwd);
}

int	builtin_pwd(t_dict *dic)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL && errno == ENOMEM)
		null_guard(NULL);
	if (pwd == NULL && find_dic(dic, "PWD") != NULL)
		null_guard(pwd = ft_strdup(find_dic(dic, "PWD")->value));
	if (pwd != NULL)
		ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
