/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_in_out_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:42:53 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/31 21:15:59 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	conf_in_out_pipe(t_node_n *n)
{
	int	rtn;

	if (n->files != NULL)
	{
		rtn = decide_in_except_heredoc(n);
		if (rtn == -1)
			return (1);
		rtn = open_other_files(n);
		if (rtn == 1)
			return (1);
		rtn = decide_out(n);
		if (rtn == 1)
			return (1);
	}
	return (0);
}

int	conf_in_out_fork(t_node_n *n, int i)
{
	int	j;

	if (i != 0)
	{
		if (dup2(g_data->pipe[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2");
	}
	if (i != g_data->pipe_count)
	{
		if (dup2(g_data->pipe[i][1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	if (conf_in_out_pipe(n) == 1)
		return (1);
	j = 0;
	while (j < g_data->pipe_count)
	{
		close(g_data->pipe[j][0]);
		close(g_data->pipe[j][1]);
		j++;
	}
	return (0);
}
