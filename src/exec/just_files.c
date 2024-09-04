/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 04:22:02 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/30 07:26:02 by yokamura         ###   ########.fr       */
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

static int	just_files_sub(t_file_n *p)
{
	if (heredoc(p->op_file) == -1)
		return (1);
	if (g_data->signal_heredoc == 1)
		return (1);
	dup2(g_data->save_in, STDIN_FILENO);
	return (0);
}

void	just_files(t_node_n *n)
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
			else if (p->type == LL)
			{
				if (just_files_sub(p) == 1)
					return ;
			}
			if (just_files_error(p, fd) == -1)
				return ;
			p = p->next;
		}
	}
}
