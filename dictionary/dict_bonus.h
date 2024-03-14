/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:17:16 by mkong             #+#    #+#             */
/*   Updated: 2024/03/14 13:29:08 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_BONUS_H
# define DICT_BONUS_H
# include "../essential_bonus.h"
# include "../error_bonus.h"

typedef struct s_dnode
{
	struct s_dnode	*prev;
	struct s_dnode	*next;
	char			*key;
	char			*value;
	int				check_env;
	int				is_ambg;
}	t_dnode;

typedef struct s_dict
{
	t_dnode	*head;
	t_dnode	*tail;
	int		env_size;
	int		exit_status;
	int		exec_flag;
}	t_dict;

// dict_insert_remove.c
int		insert_dict(t_dict *dic, char *key, char *value, int check_env);
void	remove_dic(t_dict *dic, char *key);

// dict_make_utils.c
t_dict	*init_dict(void);
t_dnode	*init_dnode(void);
t_dict	*copy_dic(t_dict *dic);
t_dnode	*find_dic(t_dict *dic, char *key);
void	free_dic(t_dict *dic);

// dict_make.c
char	**make_envp(t_dict *dic);
char	*join_key_value(char *key, char *value);
char	*get_key(char *env);
char	*get_value(char *env);
int		set_dict(t_dict *dic, char **envp);

#endif
