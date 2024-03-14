/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:51:15 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/05 09:51:16 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "token.h"
# include "essential.h"
# include "error.h"

# define INIT_SIZE 10

typedef struct s_vector
{
	void	**arr;
	int		data_type;
	int		size;
	int		capacity;
}	t_vector;

t_vector	*init_vector(int capacity);
void		push_back(t_vector *vector, void *node);
int			vector_find(t_vector *vector, void *f_node);
void		copy_vector(void **dst, void **src, int size);
void		free_vector(t_vector *vector);

#endif
