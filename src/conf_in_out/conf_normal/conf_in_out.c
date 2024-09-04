/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:57:58 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 00:33:49 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	conf_in_out(t_node_n *n)
{
	int	rtn;

	if (n->files != NULL)
	{
		rtn = here_doc_except_last(n);
		if (rtn == 1)
			return (1);
		rtn = decide_in(n);
		if (rtn == 1)
			return (1);
		if (g_data->signal_heredoc == 1)
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
