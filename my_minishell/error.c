/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:53:00 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 19:25:34 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_guard(void *str)
{
	if (str == NULL)
		exit_error(MALLOC_ERR);
}

void	exit_error(char *str)
{
	write(2, str, ft_strlen(str));
	if (ft_strncmp(str, CNF_ERR, 19) == 0)
		exit(127);
	exit(1);
}

void	syntax_error(char *str)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(str) + 2;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	null_guard(tmp);
	tmp[0] = '\'';
	i = -1;
	while (str[++i] != '\0')
		tmp[i + 1] = str[i];
	tmp[len - 1] = '\'';
	tmp[len] = '\0';
	ft_putstr_fd(SYNTAX_ERR, 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd("\n", 2);
	free(tmp);
}

void	printf_error(char *error, char *err_message, int i)
{
	ft_putstr_fd("minishell: ", 2);
	if (error != NULL)
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err_message, 2);
	if (i != -1)
		exit(i);
}

int	check_fail(int n)
{
	if (n == -1)
		printf_error("FD", "fd function error", 1);
	return (n);
}
