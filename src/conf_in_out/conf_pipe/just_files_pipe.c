/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_files_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:35:24 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 02:44:22 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	just_files_error(t_file_n *p, int fd)
{
	if ((p->type == R || p->type == RR) && fd < 0)
	{
		perror("open");
		g_data->status = 1;
		return (-1);
	}
	else if (p->type == L && fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", p->op_file);
		g_data->status = 1;
		return (-1);
	}
	if (p->type == R || p->type == RR || p->type == L)
		close(fd);
	return (0);
}

void	just_files_pipe(t_node_n *n)
{
	t_file_n	*p;
	int			fd;

	if (n->files != NULL)
	{
		p = n->files->top;
		while (p != NULL)
		{
			if (p->type == R)
				fd = open(p->op_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (p->type == RR)
				fd = open(p->op_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else if (p->type == L)
				fd = open(p->op_file, O_RDONLY, 0644);
			if (just_files_error(p, fd) == -1)
				return ;
			p = p->next;
		}
		if (n->filename != NULL)
			free(n->filename);
	}
}
