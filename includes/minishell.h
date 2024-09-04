/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:55:26 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/10 21:16:26 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "tokenizer.h"
# include "env_lst.h"
# include "minishell_utils.h"
# include "envp_create.h"

# define PATH_MAX 1024
# define SPACES " \t"
# define IDENTIFIER "!\"#$%&'()-|`@{}[];+:*<,>./?"

typedef enum e_blt
{
	EXECVE = 1,
	ECHO_NUM,
	CD_NUM,
	PWD_NUM,
	EXPORT_NUM,
	UNSET_NUM,
	ENV_NUM,
	EXIT_NUM,
}				t_blt;

typedef struct s_file_n
{
	t_token_t		type;
	char			*op_file;
	struct s_file_n	*next;
}				t_file_n;

typedef struct s_file_l
{
	size_t		size;
	t_file_n	*top;
}				t_file_l;

typedef struct s_node_n
{
	char			**cmds;
	t_file_l		*files;
	char			*filename;
	struct s_node_n	*next;
	struct s_node_n	*prev;
	t_blt			blt;
}				t_node_n;

typedef struct s_node_l
{
	t_node_n	*top;
	size_t		size;
}				t_node_l;

typedef struct s_data
{
	int			signal;
	int			signal_heredoc;
	long		status;
	int			save_in;
	int			save_out;
	int			pid;
	int			wstatus;
	int			pipe[1000][2];
	int			pipe_count;
	t_node_l	node_head;
	char		*line;
	char		*cmd_error;
	char		**envp;
	t_token_l	*tok;
	t_env_lst	*envlst;
}				t_data;

extern t_data	*g_data;

void		init_pipes_status(void);
void		free_files(t_node_n	*n);
void		free_cmds(t_node_n *n);

char		*search_path(char *filename);

void		make_new_lst(t_token_n *until);
void		free_list(void);

void		is_builtin(t_node_n *n);
void		echo_blt(t_node_n *n);
int			cd_blt(t_node_n *n);
void		pwd_blt(t_node_n *n);
int			export_blt(t_node_n *n);
int			unset_blt(t_node_n *n);
size_t		equal_len(const char *s);
void		unset_error_message2(char *s);
void		env_blt(t_node_n *n);
void		exit_blt(t_node_n *n);

int			decide_in(t_node_n *n);
int			decide_in_heredoc(t_node_n *n, int i);
int			decide_in_except_heredoc(t_node_n *n);

int			decide_out(t_node_n *n);
int			open_other_files(t_node_n *n);

int			heredoc(char *delimiter);
int			heredoc_pipe(char *delimiter, t_node_n *n, int i);

int			is_heredoc(void);
char		*heredoc_expand(char *s);
char		*strjoin_minishell(char *s1, char *s2);
char		*joined_create(char *delimiter);
void		reset_fd(void);
char		*filename_heredoc(int i);
void		unlink_filenames(int i);

int			conf_in_out(t_node_n *n);
int			conf_in_out_fork(t_node_n *n, int i);

int			heredoc_pipe_conf(t_node_n *n, int i);
int			here_doc_except_last(t_node_n *n);
int			here_doc_except_last_p(t_node_n *n, int i);

void		child_process(int i);
void		parent_process(int i);
void		wait_process(void);

void		just_files(t_node_n *n);
void		just_files_pipe(t_node_n *n);
int			exec_builtin(t_node_n *n);
void		exec_others(t_node_n *n);
void		exec_others_sans_fork(t_node_n *n);

int			exec_sans_pipe(void);
void		exec_avec_pipe(void);

void		set_status(int wstatus);

t_file_n	*make_files(t_token_n *p, t_node_n *n);
t_node_n	*make_cmds_files(t_token_n *until);
int			make_cmds_and_exec(void);

char		*equal_join(char *key, char *value);
int			identifier_check(const char *s);
int			set_envp(t_env_lst *lst);
t_env_node	*check_envp(char *key);
char		*equal_join(char *key, char *value);

void		exit_error(char *s);
void		cd_error1(char c);
void		cd_error2(char *s);
void		delete_envnode(t_env_lst *lst, t_env_node *node);

void		last_free(void);

void		set_signal_main(void);
void		set_signal_def(void);
void		set_signal_heredoc(void);
void		set_signal_ign(void);
void		wait_signal(void);

int			cumbersome_env(t_env_lst *lst);
int			shlvl(t_env_lst *lst);
int			under(t_env_lst *lst);

int			check_line(char *line);

#endif
