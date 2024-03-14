/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:00 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/13 17:49:15 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_vector	*expand_wildcard(char *pattern)
{
	char		cwd[MAX_DIRLEN];
	t_vector	*vector;
	DIR			*dir;

	if (!check_cur_dir(cwd, &dir))
		return (NULL);
	if (check_only_wc(pattern))
	{
		vector = only_wc_vector(pattern, dir);
		closedir(dir);
		return (vector);
	}
	vector = expand_wildcard_branch(pattern, dir);
	closedir(dir);
	return (vector);
}

t_vector	*only_wc_vector(char *pattern, DIR *dir)
{
	char			*ret;
	struct dirent	*entry;
	t_vector		*vector;

	vector = init_vector(INIT_SIZE);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] == '.')
			continue ;
		ret = ft_strdup(entry->d_name);
		null_guard(ret);
		push_back(vector, (void *)ret);
	}
	if (vector->size == 0)
	{
		ret = ft_strdup(pattern);
		null_guard(ret);
		push_back(vector, (void *)ret);
	}
	return (vector);
}

t_vector	*expand_wildcard_branch(char *pattern, DIR *dir)
{
	t_vector	*vector;
	char		*tmp;

	if (check_edge_wildcard(pattern))
	{
		if (pattern[0] == '*')
		{
			while (*pattern == '*')
				pattern++;
			vector = edge_wc_vector(pattern, dir, check_front_wc);
			no_pattern_matches(vector, pattern, NULL);
		}
		else
		{
			tmp = cut_wildcard(pattern);
			vector = edge_wc_vector(tmp, dir, ft_strncmp);
			no_pattern_matches(vector, pattern, tmp);
		}
	}
	else
		vector = middle_wc_vector(pattern, dir);
	return (vector);
}

t_vector	*edge_wc_vector(char *pattern, DIR *dir, \
int (*f)(const char *, const char *, size_t))
{
	char			*ret;
	struct dirent	*entry;
	t_vector		*vector;

	vector = init_vector(INIT_SIZE);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' && \
		!f(entry->d_name, pattern, ft_strlen(pattern)))
		{
			ret = ft_strdup(entry->d_name);
			null_guard(ret);
			push_back(vector, (void *)ret);
		}
	}
	return (vector);
}

t_vector	*middle_wc_vector(char *pattern, DIR *dir)
{
	char			*ret;
	struct dirent	*e;
	t_vector		*vector;
	char			**ps;

	ps = ft_split(pattern, '*');
	vector = init_vector(INIT_SIZE);
	while (1)
	{
		e = readdir(dir);
		if (e == NULL)
			break ;
		if (e->d_name[0] != '.' && check_mixed_wc(e->d_name, pattern, ps))
		{
			null_guard(ret = ft_strdup(e->d_name));
			push_back(vector, (void *)ret);
		}
	}
	if (vector->size == 0)
	{
		null_guard(ret = ft_strdup(pattern));
		push_back(vector, (void *)ret);
	}
	free_t_d(ps);
	return (vector);
}
