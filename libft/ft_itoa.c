/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:56:01 by mkong             #+#    #+#             */
/*   Updated: 2023/10/18 17:30:52 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	check_int_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	c_arr_reverse(char *s, int len)
{
	char	tmp;
	int		idx;

	idx = 0;
	while (idx < len - 1)
	{
		tmp = *(s + idx);
		*(s + idx) = *(s + len - 1);
		*(s + len - 1) = tmp;
		len--;
		idx++;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		idx;

	len = check_int_len(n);
	idx = 0;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	*(result + len) = '\0';
	if (n == 0)
		*result = '0';
	if (n < 0)
	{
		*(result + len - 1) = '-';
		*(result + idx++) = (n % 10) * (-1) + '0';
		n = n / 10 * (-1);
	}
	while (n > 0)
	{
		*(result + idx++) = n % 10 + '0';
		n /= 10;
	}
	c_arr_reverse(result, len);
	return (result);
}
