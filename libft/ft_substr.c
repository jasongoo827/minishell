/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:48:19 by mkong             #+#    #+#             */
/*   Updated: 2023/10/18 17:13:42 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*result;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		result = (char *)malloc(sizeof(char) * 1);
		if (result == 0)
			return (0);
		*result = '\0';
		return (result);
	}
	if (start + len > s_len)
		len = s_len - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
