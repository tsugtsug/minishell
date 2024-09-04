/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:31:31 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/31 20:59:06 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_signal_handler(int signal)
{
	(void)signal;
	g_data->signal_heredoc = 1;
	g_data->status = 1;
	close(0);
	write(1, "\n", 1);
	return ;
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, &heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
