/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:53:22 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 20:46:04 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC_ERR "Memory Allocate Error\n"
# define SYNTAX_ERR "minishell: syntax error near unexpected token "
# define CNF_ERR "command not found"
# define PER_ERR "Permission denied"
# define DIR_ERR "is a directory"
# define NOF_ERR "No such file or directory"
# define EXE_ERR "Exec format error"
# define AMB_ERR "ambiguous redirect"
# define HER_ERR "maximum here-document count exceeded"
# define CDD_ERR "error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory"

void	exit_error(char *str);
void	null_guard(void *str);
void	syntax_error(char *str);
void	printf_error(char *error, char *err_message, int i);
int		check_fail(int n);

#endif
