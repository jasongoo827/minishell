/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:11:54 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 15:29:47 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_heredoc_syntax(t_vector *re_vec, t_dict *dic, int i)
{
	int	j;

	if (i == re_vec->size - 1)
	{
		j = i - 1;
		syntax_error("newline");
		dic->exit_status = 258;
		while (++j < re_vec->size)
			free(re_vec->arr[j]);
		re_vec->size = i;
		return (-1);
	}
	if (check_redirect_syntax(re_vec->arr[i + 1]) < 0)
	{
		j = i - 1;
		while (++j < re_vec->size)
			free(re_vec->arr[j]);
		re_vec->size = i;
		return (-1);
	}
	return (1);
}

int	check_heredoc_exit(t_vector *re_vec, t_dict *dic, int i)
{
	int	j;

	if (heredoc_signal_exit_status() < 0)
	{
		j = i;
		while (++j < re_vec->size)
			free(re_vec->arr[j]);
		re_vec->size = i + 1;
		dic->exit_status = 1;
		return (-1);
	}
	return (1);
}

void	heredoc_etc(char *tmp_name, t_vector *re_vec, int i)
{
	char	*name;

	name = ft_strdup(tmp_name);
	null_guard(name);
	free(re_vec->arr[i]);
	free(tmp_name);
	re_vec->arr[i] = name;
}

char	*get_after_deli(char *delimeter)
{
	char	*ret;

	ret = ft_strdup(delimeter);
	null_guard(ret);
	ret = rm_quote(ret);
	return (ret);
}

void	check_deli(char *after_deli, char *s, int fd)
{
	if (ft_strncmp(s, after_deli, ft_strlen(after_deli) + 1) == 0)
	{
		free(s);
		check_fail(close(fd));
		exit(0);
	}
}
