/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:14:30 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/11 20:17:32 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

# define SPLIT_C " \t"
# define SPLIT_C2 "|<>'\""

# define HEAD_ENV "?_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
# define NO_ENV " \t~`!@#$%^&*()-+=[]{}:;\"'<>.,/\n"
# define NV "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"

typedef enum e_token_t
{
	STR = 1,
	R,
	RR,
	L,
	LL,
	PIPE,
	SPACE1,
	QUOTE,
	QQUOTE,
	NONE,
}			t_token_t;

typedef struct s_token_n
{
	char				*word;
	t_token_t			type;
	struct s_token_n	*next;
	struct s_token_n	*prev;
}				t_token_n;

typedef struct s_token_l
{
	t_token_n	*top;
	size_t		size;
}				t_token_l;

int			tokenizer(void);
t_token_n	*token_n_new(char *s);
t_token_l	*token_lst_new(void);
int			token_add(t_token_l *lst, char *str);
void		delete_node(t_token_l *lst);
void		delete_helper(t_token_l *lst, t_token_n *node);
int			path_expansion(t_token_l *lst);
void		type_classify(t_token_l *lst);
int			word_join(t_token_l *lst);
void		token_free(t_token_l *lst);
int			error_quart(t_token_l *lst);
int			syntax_error(t_token_l *lst);
t_token_l	*space_split(char *line);
int			dollar_check(const char *s, int f);
char		*expand_join(char *s1, char *s2, size_t len);
size_t		fill_space(char *s);
void		add_back(t_token_l *lst, t_token_n *new);
size_t		split_len(const char *s);
size_t		quote_len(const char *s, int flag);
size_t		equal_len(const char *s);
char		*expansion_help2(char *str, char *s, size_t *i);
char		*expand_line(char *s);
char		*env_str(char *s, size_t *i);
int			set_under_env(t_token_l *lst);
char		*env_str_quart(char *s, size_t *i, int f);

#endif
