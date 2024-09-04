/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:25:27 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 03:22:53 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_check(t_node_n *n)
{
	t_file_n	*p;

	p = n->files->top;
	if (p != NULL)
	{
		while (p != NULL)
		{
			if (p->type == LL)
				return (1);
			p = p->next;
		}
	}
	return (0);
}

t_node_n	*get_node_according_to_i(int i)
{
	t_node_n	*n;
	int			j;

	n = g_data->node_head.top;
	j = 1;
	while (j < i)
	{
		n = n->next;
		j++;
	}
	return (n);
}

int	is_heredoc(void)
{
	t_node_n	*n;
	int			i;

	i = 1;
	while (i < g_data->pipe_count + 2)
	{
		set_signal_ign();
		n = get_node_according_to_i(i);
		if (n->files != NULL)
		{
			if (heredoc_check(n) == 1)
			{
				if (heredoc_pipe_conf(n, i) == 1)
					return (1);
			}
		}
		dup2(g_data->save_in, STDIN_FILENO);
		dup2(g_data->save_out, STDOUT_FILENO);
		i++;
	}
	return (0);
}
