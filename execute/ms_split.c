/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:47:23 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 16:20:58 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*find_s(char *s, char c)
{
	if (*s == '\"' || *s == '\'')
	{
		s = ft_strchr(s + 1, *s);
		while (s != NULL && *(s + 1) != 0 && *(s + 1) != c)
		{
			if (*(s + 1) == '\"' || *(s + 1) == '\'')
				s = ft_strchr(s + 2, *(s + 1));
			else
				s++;
		}
		return (s);
	}
	else
	{
		if (ft_strchr(s, c) > ft_strchr(s, '\"') && ft_strchr(s, '\"') != 0)
			s = find_s(ft_strchr(s, '\"'), c);
		else if (ft_strchr(s, c) > ft_strchr(s, '\'')
			&& ft_strchr(s, '\'') != 0)
			s = find_s(ft_strchr(s, '\''), c);
		else
			s = ft_strchr(s, c) - 1;
	}
	return (s);
}

static char	**make_ret(t_vector *words)
{
	char	**ret;
	int		i;

	i = -1;
	ret = (char **)malloc((words->size + 1) * sizeof(char *));
	null_guard(ret);
	while (++i < words->size)
	{
		ret[i] = ft_strdup(words->arr[i]);
		null_guard(ret[i]);
		free(words->arr[i]);
	}
	ret[i] = NULL;
	return (ret);
}

char	**ms_split(char	*s, char c)
{
	t_vector	*words;
	char		*word;
	char		**ret;

	words = init_vector(INIT_SIZE);
	null_guard(words);
	while (s && *s)
	{
		if (*s == c)
			s++;
		else
		{
			word = ft_substr(s, 0, find_s(s, c) - s + 1);
			null_guard(word);
			push_back(words, word);
			if (find_s(s, c) == NULL)
				break ;
			s = find_s(s, c) + 1;
		}
	}
	ret = make_ret(words);
	free_vector(words);
	return (ret);
}
