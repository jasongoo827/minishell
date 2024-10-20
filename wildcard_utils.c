/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:51 by jgoo              #+#    #+#             */
/*   Updated: 2024/10/21 01:47:01 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	check_cur_dir(char *cwd, DIR **dir)
{
	if (getcwd(cwd, MAX_DIRLEN) == NULL)
	{
		perror("getcwd error\n");
		return (0);
	}
	*dir = opendir(cwd);
	if (*dir == NULL)
	{
		perror("opendir error\n");
		return (0);
	}
	return (1);
}

int	check_only_wc(char *pattern)
{
	int	i;

	i = -1;
	while (pattern[++i] != '\0')
	{
		if (pattern[i] != '*')
			return (0);
	}
	return (1);
}

int	check_front_wc(const char *str, const char *pattern, size_t len)
{
	int	j;

	j = (int)(ft_strlen(str) - len);
	if (j < 0)
		return (1);
	while (j--)
		str++;
	if (ft_strncmp(str, pattern, len) != 0)
		return (1);
	return (0);
}

char	*cut_wildcard(char *pattern)
{
	char	*ret;
	int		len;

	len = 0;
	while (pattern[len] && pattern[len] != '*')
		len++;
	ret = ft_substr(pattern, 0, len);
	null_guard(ret);
	return (ret);
}

int	check_mixed_wc(char *str, char *pattern, char **patterns)
{
	int		i;
	int		len;

	i = -1;
	while (patterns[++i] != NULL)
	{
		len = ft_strlen(patterns[i]);
		// 맨 앞이 '*'로 시작하지 않을 때, 패턴 확인
		if (i == 0 && find_pattern_front(str, pattern, patterns[i], len))
			return (0);
		else if (patterns[i + 1] != NULL)
		{
			// str에 패턴 있는지 확인
			if (find_pattern_in_str(&str, patterns[i], len) < 0)
				return (0);
			continue ;
		}
		else if ((pattern[ft_strlen(pattern) - 1] != '*' && \
		check_mixed_wc_branch(str, patterns[i], len) < 0) || \
		!ft_strnstr(str, patterns[i], ft_strlen(str)))
			return (0);
		move_str(&str, len);
	}
	return (1);
}
