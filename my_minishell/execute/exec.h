/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:20:24 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 12:29:40 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "../dictionary/dict.h"
# include "../vector.h"
# include "../tree.h"
# include "../builtin/builtin.h"
# include "../signal.h"
# include "../error.h"
# include "../wildcard.h"
# include "../minishell.h"
# define IN_FD 1
# define OUT_FD 2

typedef enum e_builtin
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
	ELSE
}	t_builtin;

typedef struct s_cnode
{
	struct s_cnode	*next;
	t_vector		*cmd_vec;
	t_vector		*re_vec;
	t_dict			*old_dic;
	t_builtin		b_category;
	char			*path;
	int				*fds;
	int				*input_fd;
	int				*output_fd;
	int				pipe;
}	t_cnode;

typedef struct s_cmdlst
{
	t_cnode		*head;
	t_cnode		*tail;
	t_dict		*dic;
	int			pre_exit_status;
	int			size;
	int			fds[2];
	int			child;
	int			input_fd;
	int			output_fd;
}	t_cmdlst;

// here_doc.c
char		*make_here_name(void);
int			here_doc(t_vector *re_vec, t_dict *dic);
void		delete_here_doc(t_vector *re_vec);
void		count_here_doc(t_vector *re_vec);

// here_doc_utils.c
t_vector	*root_re_vec(t_node *root, t_dict *dic, int *re_flag);
void		change_root_hcontent(t_node *root, t_vector *all_re_vec);
int			check_redirect_syntax(char *content);

// here_doc_utils2.c
int			check_heredoc_syntax(t_vector *re_vec, t_dict *dic, int i);
int			check_heredoc_exit(t_vector *re_vec, t_dict *dic, int i);
void		heredoc_etc(char *tmp_name, t_vector *re_vec, int i);
char		*get_after_deli(char *delimeter);
void		check_deli(char *after_deli, char *s, int fd);

// exec_cmd.c
char		**find_path(t_dict *dic);
char		*make_path(t_cnode *node);

// exec_cmd_utils.c
int			check_fd(int n, char *path, int in_out, int is_parent);
int			check_ambgious(char *path, int is_parent);
void		free_cmdlst(t_cmdlst *lst);
void		check_path(char *path);
void		free_t_d(char **cmd);

// exec_cmdlst_maker.c
t_cmdlst	*init_cmdlst(t_dict *dic);
t_cmdlst	*make_cmdlst(t_node *root, t_dict *dic);
t_cnode		*init_cnode(t_dict *dic);

// exec_cmdlst_utils.c
t_builtin	check_builtin(char *cmd);
void		make_cmd_vec(t_dict *d, t_node *rt, t_vector *c_v, t_vector *r_v);
void		insert_cnode(t_cmdlst *lst, t_vector *cmd_vec, t_vector *re_vec);

// exec_utils.c
int			exec_builtin(t_cnode *node, int is_parent, int pre_exit);
int			is_whitespace(char c);
void		pipe_handler(t_cnode *node);
int			re_handler(t_vector *r_v, t_dict *dic, int is_parent);

// exec_utils2.c
int			exec_pline(t_node *root, t_node *node, t_dict *dic);
int			exec_and(t_node *root, t_node *node, t_dict *dic);
int			exec_or(t_node *root, t_node *node, t_dict *dic);
int			check_syntax_error(t_node *node, t_node *scmd, t_dict *dic, int i);
t_node		*find_list_node(t_node *node);

// exec_utils3.c
int			check_subshell(t_node *root, t_dict *dic);
int			check_between_pipe(t_node *root, t_dict *dic, int i);

// exec.c
void		exec_cmd(t_cmdlst *lst, t_dict *dic);
void		execute(t_node *root, t_dict *dic, int *re_flag);

// exec_and_or.c
int			check_pipeline(t_node *root);
int			check_pipe(t_node *roo, t_dict *dic);
int			check_error_node(t_node *root, t_dict *dic);
int			check_re_content(t_vector *vector);

// expansion.c
t_vector	*expansion_vec(t_vector *cmd_vec, t_dict *dic, int re);
t_builtin	check_builtin(char *cmd);
char		*merge_cmd_vec(t_vector *cmd_vec);
char		*change_env(t_dict *dic, char *arg, int re);
void		push_cmd(t_vector *ret_vec, char *cmd);

// expansion_utils.c
char		*change_env_question(t_dict *dic, char *arg, int *i);
char		*change_env_normal(t_dict *dic, char *arg, int *i, int re);

// ms_split.c
char		**ms_split(char	*s, char c);

#endif
