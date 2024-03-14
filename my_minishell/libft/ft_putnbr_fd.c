/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:12:07 by mkong             #+#    #+#             */
/*   Updated: 2023/10/18 17:29:44 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	n_array[10];
	int		count;

	count = 0;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		write(fd, "-", 1);
		n = (-1) * n;
	}
	while (n != 0)
	{
		*(n_array + count) = n % 10 + '0';
		n /= 10;
		++count;
	}
	while (--count != -1)
		write(fd, n_array + count, 1);
}
