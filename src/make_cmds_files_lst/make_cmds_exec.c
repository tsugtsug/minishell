/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:04:42 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/03 02:59:53 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status(int wstatus)
{
	if (wstatus == 256)
		g_data->status = 1;
	else if (wstatus == 512)
		g_data->status = 127;
	else if (wstatus == 2 || wstatus == 3)
		g_data->status = wstatus + 128;
	else
		g_data->status = WEXITSTATUS(wstatus);
}

int	exec_according_to_pipe(void)
{
	if (g_data->pipe_count != 0)
		exec_avec_pipe();
	else
	{
		if (!exec_sans_pipe())
		{
			init_pipes_status();
			return (0);
		}
	}
	init_pipes_status();
	return (1);
}

int	make_cmds_and_exec(void)
{
	t_token_n	*p;

	p = g_data->tok->top;
	while (p != NULL)
	{
		if (ft_strcmp(p->word, "|") == 0)
		{
			if (make_cmds_files(p) == NULL)
				return (1);
			make_new_lst(p);
			p = g_data->tok->top;
			g_data->pipe_count++;
		}
		p = p->next;
	}
	if (p == NULL)
	{
		if (make_cmds_files(p) == NULL)
			return (1);
		free_list();
	}
	if (!exec_according_to_pipe())
		return (0);
	return (1);
}
