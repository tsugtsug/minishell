/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe_conf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:14:10 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 03:20:58 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_pipe_conf(t_node_n *n, int i)
{
	int			rtn;

	if (n->files != NULL)
	{
		rtn = here_doc_except_last_p(n, i);
		if (rtn == 1)
			return (1);
		rtn = decide_in_heredoc(n, i);
		if (rtn == 1)
			return (1);
	}
	return (0);
}
