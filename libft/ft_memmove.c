/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:26:52 by mkong             #+#    #+#             */
/*   Updated: 2023/10/18 18:54:15 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_tmp;
	const unsigned char	*src_tmp;

	dst_tmp = (unsigned char *)dst;
	src_tmp = (const unsigned char *)src;
	if (dst || src)
	{
		if (dst <= src)
		{
			while (len-- > 0)
				*dst_tmp++ = *src_tmp++;
		}
		else
		{
			dst_tmp += len - 1;
			src_tmp += len - 1;
			while (len-- > 0)
				*dst_tmp-- = *src_tmp--;
		}
	}
	return (dst);
}
