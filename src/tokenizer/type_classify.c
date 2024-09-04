/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_classify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:09:12 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/10 21:27:48 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rl_type(t_token_n *node)
{
	if (node->word[0] == '>')
	{
		if (!ft_strncmp(">>", node->word, 2))
			node->type = RR;
		else
			node->type = R;
	}
	else if (node->word[0] == '<')
	{
		if (!ft_strncmp("<<", node->word, 2))
			node->type = LL;
		else
			node->type = L;
	}
}

static int	space_check(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(" \t", s[i]))
			return (0);
		i += 1;
	}
	return (1);
}

static void	type_node(t_token_n *node, int *f)
{
	if ((*f == 0 || *f == 1) && !ft_strcmp(node->word, "'"))
	{
		node->type = QUOTE;
		if (*f == 1)
			*f = 0;
		else
			*f = 1;
	}
	else if ((*f == 0 || *f == 2) && !ft_strcmp(node->word, "\""))
	{
		node->type = QQUOTE;
		if (*f == 2)
			*f = 0;
		else
			*f = 2;
	}
	else if (*f == 0 && !ft_strcmp(node->word, "|"))
		node->type = PIPE;
	else if (*f == 0 && space_check(node->word))
		node->type = SPACE1;
	else if (*f == 0 && ft_strlen(node->word) < 3
		&& ft_strchr("<>", node->word[0]))
		rl_type(node);
	else
		node->type = STR;
}

void	type_classify(t_token_l *lst)
{
	t_token_n	*tmp;
	int			f;

	tmp = lst->top;
	f = 0;
	while (tmp != NULL)
	{
		type_node(tmp, &f);
		tmp = tmp->next;
	}
}
