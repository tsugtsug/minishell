/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:51:01 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/31 19:39:38 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_node_n *n)
{
	int	i;

	if (n->cmds != NULL)
	{
		i = 0;
		while (n->cmds[i])
		{
			free(n->cmds[i]);
			i++;
		}
		free(n->cmds);
		n->cmds = NULL;
	}
}

void	free_files(t_node_n	*n)
{
	t_file_n	*p;
	t_file_n	*tmp;

	if (n->files != NULL)
	{
		p = n->files->top;
		while (p != NULL)
		{
			tmp = p->next;
			free(p->op_file);
			free(p);
			p = tmp;
		}
		free(n->files);
		n->files = NULL;
	}
}

void	free_nodes(void)
{
	t_node_n	*n;
	t_node_n	*tmp;

	n = g_data->node_head.top;
	if (n != NULL)
	{
		while (n != NULL)
		{
			tmp = n->next;
			free_cmds(n);
			free_files(n);
			free(n);
			n = tmp;
		}
		g_data->node_head.top = NULL;
		g_data->node_head.size = 0;
	}
}

void	init_pipes_status(void)
{
	free_nodes();
	g_data->node_head.size = 0;
	g_data->node_head.top = NULL;
	g_data->pipe_count = 0;
	g_data->signal = 0;
	dup2(g_data->save_out, STDOUT_FILENO);
	dup2(g_data->save_in, STDIN_FILENO);
}
