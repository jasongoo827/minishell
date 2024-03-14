/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:11:05 by mkong             #+#    #+#             */
/*   Updated: 2024/03/06 18:13:34 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ret_only_one(char *s1, char *s2)
{
	char	*result;

	result = NULL;
	if (s1 == NULL && s2 != NULL)
	{
		result = ft_strdup(s2);
		if (result == NULL)
			return (NULL);
	}
	else if (s1 != NULL && s2 == NULL)
	{
		result = ft_strdup(s1);
		if (result == NULL)
			return (NULL);
	}
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL || s2 == NULL)
		return (ret_only_one((char *)s1, (char *)s2));
	else if (s1 != NULL && s2 == NULL)
		return (ret_only_one((char *)s1, (char *)s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == NULL)
		return (NULL);
	*result = '\0';
	ft_strlcat(result, s1, s1_len + 1);
	ft_strlcat(result, s2, s1_len + s2_len + 1);
	return (result);
}
