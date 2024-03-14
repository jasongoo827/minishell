/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:04:29 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 12:32:22 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../dictionary/dict.h"
# include "../vector.h"
# include "../execute/exec.h"

// builtin_cd.c
int		builtin_cd(t_dict *dic, t_vector *cmd_vec);

// builtin_echo.c
int		builtin_echo(t_vector *cmd_vec);

// builtin_env.c
char	*ft_strndup(const char *s1, size_t n);
char	*remove_twin(char *cmd, char c, int *i);
char	*rm_quote(char *cmd);
int		builtin_env(t_vector *cmd_vec, t_dict *dic);

// builtin_exit.c
int		builtin_exit(t_vector *cmd_vec, int is_parent, int pre_exit);

// builtin_export.c
int		builtin_export(t_dict *dic, t_vector *cmd_vec);

// builtin_pwd.c
char	*get_pwd(void);
int		builtin_pwd(t_dict *dic);

// builtin_unset.c
int		builtin_unset(t_dict *dic, t_vector *cmd_vec);

#endif
