/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:14:29 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 02:48:40 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(int i)
{
	if (i > 0)
	{
		close(g_data->pipe[i - 1][0]);
		close(g_data->pipe[i - 1][1]);
	}
}

void	wait_signal(void)
{
	if (g_data->wstatus == SIGINT)
		printf("\n");
	if (g_data->wstatus == SIGQUIT)
		printf("Quit :3\n");
}

void	wait_process(void)
{
	int	i;

	i = 0;
	set_signal_ign();
	while (i < g_data->pipe_count + 1)
	{
		wait(&g_data->wstatus);
		i++;
	}
	set_status(g_data->wstatus);
	wait_signal();
}
