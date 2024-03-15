/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:50:41 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 19:14:06 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "essential.h"
# include "error.h"

typedef enum e_token_category
{
	T_WORD,
	T_PIPE,
	T_OR,
	T_AND,
	T_IN_RE,
	T_OUT_RE,
	T_HERE_RE,
	T_APPEND_RE,
	T_LPARENT,
	T_RPARENT,
	T_ERROR,
	T_HEAD
}	t_token_category;

typedef struct s_token
{
	char				*content;
	t_token_category	category;
	struct s_token		*next;
}	t_token;

// tokenize.c
t_token	*create_token(char *content, t_token_category category);
void	add_token(t_token **head, t_token *token);
void	tokenize(char *input, t_token *head);
void	free_tokenlist(t_token *head);
int		check_blank(char c);

// tokenize_utils1.c
void	tokenize_and(char *str, t_token *head, int *idx, int *flag);
void	tokenize_pipe(char *str, t_token *head, int *idx, int *flag);
void	tokenize_out_redir(char *str, t_token *head, int *idx, int *flag);
void	tokenize_in_redir(char *str, t_token *head, int *idx, int *flag);
void	tokenize_parent(char *str, t_token *head, t_token_category category);

// tokenize_utils2.c
int		check_word(char c);
int		check_char(char *str, char c);
int		check_quote_cnt(char *str, char c);
void	tokenize_word_branch(char *str, t_token *head, int *idx);
char	*tokenize_quote(char *str, char c);

// tokenize_utils3.c
int		check_word_quote_space(char *str, char c);
void	tokenize_word(char *ret, char *q_str, t_token *head, int *idx);
void	tokenize_error(char *str, t_token *head, int *idx, int len);
void	update_parent_token(t_token *head);

// tokenize_utils4.c
void	tokenize_meta_char(char *str, t_token *head, \
t_token_category category);
void	tokenize_meta_char_error(char *str, t_token *head, int len);
int		move_idx(char *str, int *idx, int *flag, char c);
void	update_lparent_error(t_token *head, int cnt, int p_cnt);
void	update_rparent_error(t_token *head, int cnt);

// tokenize_utils5.c
void	update_error_token(t_token *head);
void	find_quote_char(char *str, char *c);
void	tokenize_meta_branch(char *str, t_token *head, t_token_category c, \
int *flag);
void	tokenize_branch(char *input, t_token *head, int *i, int *flag);
void	print_tokenlist(t_token *head);

#endif
