/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:50:47 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:33:52 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"

t_vector	*init_vector(int capacity)
{
	t_vector	*vector;

	vector = (t_vector *)malloc(sizeof(t_vector));
	null_guard(vector);
	if (capacity == 0)
		capacity = INIT_SIZE;
	vector->arr = (void **)malloc(sizeof(void *) * capacity);
	null_guard(vector->arr);
	ft_bzero(vector->arr, sizeof(void *) * capacity);
	vector->data_type = sizeof(void *);
	vector->size = 0;
	vector->capacity = capacity;
	return (vector);
}

void	push_back(t_vector *vector, void *node)
{
	void	**tmp;

	if (vector->size == vector->capacity)
	{
		tmp = malloc(sizeof(void *) * (vector->capacity * 2));
		null_guard(tmp);
		vector->capacity *= 2;
		copy_vector(tmp, vector->arr, vector->size);
		free(vector->arr);
		vector->arr = tmp;
	}
	vector->arr[vector->size] = node;
	vector->size++;
}

int	vector_find(t_vector *vector, void *f_node)
{
	int	i;

	i = 0;
	while (i < vector->size * vector->data_type)
	{
		if (vector->arr[i] == f_node)
			return (i);
		i += vector->data_type;
	}
	return (-1);
}

void	copy_vector(void **dst, void **src, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		dst[i] = src[i];
}

void	free_vector(t_vector *vector)
{
	if (vector == NULL)
		return ;
	if (vector->arr != NULL)
		free(vector->arr);
	free(vector);
}
