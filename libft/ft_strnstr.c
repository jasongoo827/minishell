/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:48:10 by mkong             #+#    #+#             */
/*   Updated: 2023/11/10 15:09:25 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	idx;

	if (haystack == 0 && len == 0)
		return (0);
	if (!(*needle))
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	if (ft_strlen(haystack) < len)
		len = ft_strlen(haystack);
	idx = 0;
	while (idx + needle_len <= len)
	{
		if (!ft_strncmp(haystack + idx, needle, needle_len))
			return ((char *)(haystack + idx));
		idx++;
	}
	return (0);
}
