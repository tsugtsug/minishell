/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:00:34 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/13 00:21:50 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quorte_split2(char *line, char *last_s, int *f)
{
	char	*str;

	str = NULL;
	if (*f == 1 && line[0] == '\'')
	{
		if (!ft_strcmp(last_s, "'"))
			str = ft_strdup("");
		else
		{
			str = ft_strndup(line, 1);
			*f = 0;
		}
	}
	else if (*f == 2 && line[0] == '"')
	{
		if (!ft_strcmp(last_s, "\""))
			str = ft_strdup("");
		else
		{
			str = ft_strndup(line, 1);
			*f = 0;
		}
	}
	return (str);
}

static char	*quorte_split(char *line, int *f, t_token_l *lst)
{
	char		*str;
	t_token_n	*last;

	last = lst->top;
	while (last->next != NULL)
		last = last->next;
	str = NULL;
	if (quote_len(line, *f) > 0)
		str = ft_strndup(line, quote_len(line, *f));
	else if (*f != 0)
		str = quorte_split2(line, last->word, f);
	return (str);
}

static char	*split_type(char *line, int *f, t_token_l *lst)
{
	char	*str;

	str = NULL;
	if (*f == 0)
	{
		if (ft_strchr("'\"", line[0]))
		{
			str = ft_strndup(line, 1);
			if (line[0] == '\'')
				*f = 1;
			else if (line[0] == '"')
				*f = 2;
		}
		else if ((!ft_strncmp("<<", line, 2)) || (!ft_strncmp(">>", line, 2)))
			str = ft_strndup(line, 2);
		else if (ft_strchr(SPLIT_C2, line[0]))
			str = ft_strndup(line, 1);
		else if (ft_strchr(SPLIT_C, line[0]))
			str = ft_strndup(line, space_len(line));
		else
			str = ft_strndup(line, split_len(line));
	}
	else
		str = quorte_split(line, f, lst);
	return (str);
}

static int	word_add(t_token_l *lst, char *line)
{
	size_t		i;
	t_token_n	*node;
	char		*str;
	int			f;

	i = fill_space(line);
	f = 0;
	while (line[i])
	{
		str = split_type(&line[i], &f, lst);
		if (str == NULL)
			return (0);
		i += ft_strlen(str);
		node = token_n_new(str);
		if (node == NULL)
			return (0);
		add_back(lst, node);
	}
	return (1);
}

t_token_l	*space_split(char *line)
{
	t_token_l	*lst;

	lst = token_lst_new();
	if (lst == NULL)
		return (NULL);
	if (!word_add(lst, line))
	{
		token_free(lst);
		return (NULL);
	}
	return (lst);
}
