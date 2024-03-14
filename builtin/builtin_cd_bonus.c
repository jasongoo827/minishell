/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:48:42 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 13:28:01 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

static void	cd_set_pwd_sub(t_dict *dic)
{
	t_dnode	*node;
	char	*pwd;

	if (find_dic(dic, "OLDPWD") != NULL)
	{
		if (find_dic(dic, "PWD") == NULL)
			insert_dict(dic, "OLDPWD", NULL, 1);
		else
		{
			node = find_dic(dic, "PWD");
			insert_dict(dic, "OLDPWD", node->value, 1);
		}
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL && errno == ENOMEM)
		null_guard(NULL);
	if (pwd == NULL)
		printf_error("cd", CDD_ERR, -1);
	if (find_dic(dic, "PWD") != NULL)
	{
		if (pwd == NULL)
			null_guard(pwd = ft_strjoin(find_dic(dic, "PWD")->value, "/."));
		insert_dict(dic, "PWD", pwd, 1);
	}
	free(pwd);
}

static int	cd_set_pwd(t_dict *dic, char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd : ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	cd_set_pwd_sub(dic);
	return (1);
}

int	builtin_cd(t_dict *dic, t_vector *cmd_vec)
{
	if (cmd_vec->size == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: No argument\n", 2);
		return (1);
	}
	if (ft_strlen(cmd_vec->arr[1]) > 255)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd_vec->arr[1], 2);
		ft_putstr_fd(": File name too long\n", 2);
		return (1);
	}
	else
	{
		if (cd_set_pwd(dic, cmd_vec->arr[1]) == 0)
			return (1);
	}
	return (0);
}
