/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_except_last_p.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:15:21 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 03:20:21 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	except_last_sub_p(t_file_n *last, t_node_n *n, int i)
{
	t_file_n	*p;

	p = n->files->top;
	while (p != last)
	{
		if (p->type == LL)
		{
			if (heredoc_pipe(p->op_file, NULL, -1) == -1
				|| g_data->signal_heredoc == 1)
			{
				unlink(".heredoc");
				unlink_filenames(i);
				g_data->status = 1;
				return (1);
			}
			unlink(".heredoc");
			dup2(g_data->save_in, STDIN_FILENO);
		}
		p = p->next;
	}
	return (0);
}

int	here_doc_except_last_p(t_node_n *n, int i)
{
	t_file_n	*p;
	t_file_n	*last;

	p = n->files->top;
	last = NULL;
	while (p != NULL)
	{
		if (p->type == L || p->type == LL)
			last = p;
		p = p->next;
	}
	if (last != NULL)
		return (except_last_sub_p(last, n, i));
	return (0);
}
