/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide_in_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:44:29 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 03:25:58 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_filenames(int i)
{
	t_node_n	*n;
	int			j;

	j = 1;
	n = g_data->node_head.top;
	while (j < i + 1)
	{
		if (n->filename != NULL)
		{
			unlink(n->filename);
			free(n->filename);
			n->filename = NULL;
		}
		n = n->next;
		j++;
	}
}

static int	decide_in_heredoc_sub(t_file_n *last, t_node_n *n, int i)
{
	if (heredoc_pipe(last->op_file, n, i) == 1 || g_data->signal_heredoc == 1)
	{
		unlink_filenames(i);
		g_data->status = 1;
		return (1);
	}
	return (0);
}

int	decide_in_heredoc(t_node_n *n, int i)
{
	t_file_n	*p;
	t_file_n	*last;

	p = n->files->top;
	last = NULL;
	while (p != NULL)
	{
		if (p->type == LL)
			last = p;
		p = p->next;
	}
	if (last != NULL)
		return (decide_in_heredoc_sub(last, n, i));
	return (0);
}
