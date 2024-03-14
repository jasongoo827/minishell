/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:51:35 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:34:28 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

int	check_edge_wildcard(char *pattern)
{
	char	*front;
	char	*end;

	front = ft_strchr((const char *)pattern, '*');
	end = ft_strrchr((const char *)pattern, '*');
	if (front == end)
		return (1);
	while (front != end)
	{
		if (*front != '*')
			return (0);
		front++;
	}
	return (1);
}

int	check_mixed_wc_branch(char *str, char *pattern, int len)
{
	int	j;

	j = (int)(ft_strlen(str) - ft_strlen(pattern));
	if (j < 0)
		return (-1);
	while (j--)
		str++;
	if (ft_strncmp(str, pattern, len))
		return (-1);
	return (1);
}

int	find_pattern_in_str(char **str, char *pattern, int len)
{
	char	*s;
	char	*tmp;

	s = *str;
	tmp = ft_strnstr(s, pattern, ft_strlen(s));
	if (tmp == NULL)
		return (-1);
	s = tmp;
	s += len;
	*str = s;
	return (1);
}

int	find_pattern_front(char *str, char *o_pattern, char *pattern, int len)
{
	if (o_pattern[0] != '*' && ft_strncmp(str, pattern, len))
		return (1);
	else if (!ft_strnstr(str, pattern, ft_strlen(str)))
		return (1);
	return (0);
}

void	no_pattern_matches(t_vector *vector, char *p, char *tmp)
{
	char	*pattern;

	null_guard(pattern = ft_strdup(p));
	if (vector->size == 0)
		push_back(vector, (void *)pattern);
	else
		free(pattern);
	if (tmp != NULL)
		free(tmp);
}
