/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:51:15 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:34:02 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_BONUS_H
# define VECTOR_BONUS_H

# include "token_bonus.h"
# include "essential_bonus.h"
# include "error_bonus.h"

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
