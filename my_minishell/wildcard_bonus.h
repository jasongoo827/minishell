/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:52:25 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:34:22 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include "essential_bonus.h"
# include "error_bonus.h"
# include "vector_bonus.h"
# include "./execute/exec_bonus.h"

# define MAX_DIRLEN 256

// wildcard.c
t_vector	*expand_wildcard(char *pattern);
t_vector	*only_wc_vector(char *pattern, DIR *dir);
t_vector	*expand_wildcard_branch(char *pattern, DIR *dir);
t_vector	*edge_wc_vector(char *pattern, DIR *dir, \
							int (*f)(const char *, const char *, size_t));
t_vector	*middle_wc_vector(char *pattern, DIR *dir);

// wildcard_utils.c
int			check_cur_dir(char *cwd, DIR **dir);
int			check_only_wc(char *pattern);
int			check_front_wc(const char *str, const char *pattern, size_t len);
char		*cut_wildcard(char *pattern);
int			check_mixed_wc(char *str, char *pattern, char **patterns);

// wildcard_utils2.c
int			check_edge_wildcard(char *pattern);
int			check_mixed_wc_branch(char *str, char *pattern, int len);
int			find_pattern_in_str(char **str, char *pattern, int len);
int			find_pattern_front(char *str, char *o_pattern, char *pattern, \
int len);
void		no_pattern_matches(t_vector *vector, char *p, char *tmp);

// wildcard_utils3.c
void		move_str(char **str, int len);

#endif
