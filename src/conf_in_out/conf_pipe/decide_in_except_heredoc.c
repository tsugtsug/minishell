/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide_in_except_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:18:28 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 02:46:09 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_message(t_file_n *last)
{
	if (last->type == L)
		printf("minshell: %s: No such file or directory\n", last->op_file);
	else
		printf("minshell: heredoc error\n");
}

static int	except_heredoc_sub(t_node_n *n, t_file_n *last)
{
	int	fd;

	if (last->type == L)
		fd = open(last->op_file, O_RDONLY, 0644);
	if (last->type == LL)
		fd = open(n->filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		error_message(last);
		g_data->status = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (last->type == LL)
	{
		if (unlink(n->filename) != 0)
		{
			perror("unlink");
			free(n->filename);
			return (1);
		}
		free(n->filename);
	}
	return (0);
}

int	decide_in_except_heredoc(t_node_n *n)
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
		return (except_heredoc_sub(n, last));
	return (0);
}
