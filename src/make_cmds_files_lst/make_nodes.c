/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:27:35 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 02:40:50 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nodes_init(t_node_n *n)
{
	n->cmds = NULL;
	n->files = NULL;
	n->filename = NULL;
	n->next = NULL;
	n->prev = NULL;
	n->blt = 1;
	g_data->node_head.size++;
}

char	**get_size_and_malloc_cmds(t_token_n *until, t_node_n *n)
{
	size_t		i;
	t_token_n	*p;

	i = 0;
	p = g_data->tok->top;
	while (p != until)
	{
		if (p->type == R || p->type == L || p->type == RR || p->type == LL)
		{
			p = p->next->next;
			continue ;
		}
		p = p->next;
		i++;
	}
	n->cmds = (char **)malloc(sizeof(char *) * (i + 1));
	n->cmds[i] = NULL;
	return (n->cmds);
}

void	put_last_nodes(t_node_n *n)
{
	t_node_n	*p;
	t_node_n	*tmp;

	p = g_data->node_head.top;
	if (p == NULL)
	{
		g_data->node_head.top = n;
		n->prev = NULL;
	}
	else
	{
		while (p != NULL)
		{
			tmp = p;
			p = p->next;
		}
		tmp->next = n;
		n->prev = tmp;
	}
	nodes_init(n);
}

t_node_n	*malloc_for_nodes(t_token_n *until)
{
	t_node_n	*n;

	n = (t_node_n *)malloc(sizeof(t_node_n));
	if (n == NULL)
		return (NULL);
	put_last_nodes(n);
	n->cmds = get_size_and_malloc_cmds(until, n);
	if (n->cmds == NULL)
		return (NULL);
	return (n);
}

t_node_n	*make_cmds_files(t_token_n *until)
{
	t_token_n	*p;
	t_node_n	*n;
	size_t		i;

	i = 0;
	p = g_data->tok->top;
	n = malloc_for_nodes(until);
	if (n == NULL)
		return (NULL);
	while (p != until)
	{
		if (p->type == R || p->type == L || p->type == RR || p->type == LL)
		{
			if (make_files(p, n) == NULL)
				return (NULL);
			p = p->next->next;
			continue ;
		}
		n->cmds[i] = p->word;
		p = p->next;
		i++;
	}
	n->cmds[i] = NULL;
	is_builtin(n);
	return (n);
}
