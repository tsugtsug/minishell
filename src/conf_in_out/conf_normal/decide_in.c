/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:56:51 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/30 08:14:42 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc_except_last_sub(t_file_n *last, t_node_n *n)
{
	t_file_n	*p;

	p = n->files->top;
	while (p != last)
	{
		if (p->type == LL)
		{
			if (heredoc(p->op_file) == -1)
			{
				g_data->status = 1;
				return (1);
			}
			if (g_data->signal_heredoc == 1)
			{
				g_data->status = 1;
				return (1);
			}
			dup2(g_data->save_in, STDIN_FILENO);
		}
		p = p->next;
	}
	return (0);
}

int	here_doc_except_last(t_node_n *n)
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
		return (here_doc_except_last_sub(last, n));
	return (0);
}

static int	decide_in_sub(t_file_n *last)
{
	int	fd;

	if (last->type == L)
	{
		fd = open(last->op_file, O_RDONLY, 0644);
		if (fd < 0)
		{
			printf("minshell: %s: No such file or directory\n", last->op_file);
			g_data->status = 1;
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (last->type == LL)
	{
		if (heredoc(last->op_file) == -1 || g_data->signal_heredoc == 1)
		{
			g_data->status = 1;
			return (1);
		}
	}
	return (0);
}

int	decide_in(t_node_n *n)
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
		return (decide_in_sub(last));
	return (0);
}
