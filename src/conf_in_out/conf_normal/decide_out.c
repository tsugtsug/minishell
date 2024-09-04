/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:37:20 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/23 02:50:04 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_other_files_sub(t_node_n *n, t_file_n *last)
{
	t_file_n	*p;
	int			fd;

	p = n->files->top;
	while (p != last)
	{
		if (p->type == R)
			fd = open(p->op_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (p->type == RR)
			fd = open(p->op_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open");
			g_data->status = 1;
			return (1);
		}
		if (p->type == R || p->type == RR)
			close(fd);
		p = p->next;
	}
	return (0);
}

int	open_other_files(t_node_n *n)
{
	t_file_n	*p;
	t_file_n	*last;

	p = n->files->top;
	last = NULL;
	while (p != NULL)
	{
		if (p->type == R || p->type == RR)
			last = p;
		p = p->next;
	}
	if (last != NULL)
		return (open_other_files_sub(n, last));
	return (0);
}

static int	decide_out_sub(t_file_n *last)
{
	int	fd;

	if (last->type == R)
		fd = open(last->op_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(last->op_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		g_data->status = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	decide_out(t_node_n *n)
{
	t_file_n	*p;
	t_file_n	*last;

	p = n->files->top;
	last = NULL;
	while (p != NULL)
	{
		if (p->type == R || p->type == RR)
			last = p;
		p = p->next;
	}
	if (last != NULL)
		return (decide_out_sub(last));
	return (0);
}
