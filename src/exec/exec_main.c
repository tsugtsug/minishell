/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:16:23 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/09 17:56:41 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_node_n *n)
{
	if (n->blt == ECHO_NUM)
		echo_blt(n);
	else if (n->blt == CD_NUM)
	{
		if (!cd_blt(n))
			return (0);
	}
	else if (n->blt == PWD_NUM)
		pwd_blt(n);
	else if (n->blt == EXPORT_NUM)
	{
		if (!export_blt(n))
			return (0);
	}
	else if (n->blt == UNSET_NUM)
	{
		if (!unset_blt(n))
			return (0);
	}
	else if (n->blt == ENV_NUM)
		env_blt(n);
	else if (n->blt == EXIT_NUM)
		exit_blt(n);
	return (1);
}

static void	exec_others_sub(t_node_n *n)
{
	g_data->cmd_error = ft_strdup(n->cmds[0]);
	if (n->cmds[0] != NULL)
		n->cmds[0] = search_path(n->cmds[0]);
	if (n->cmds[0] == NULL)
	{
		error_write("minishell: %s: command not found\n", g_data->cmd_error, 2);
		free(g_data->cmd_error);
		exit(2);
	}
	free(g_data->cmd_error);
	set_signal_def();
	execve(n->cmds[0], n->cmds, g_data->envp);
	perror("execve");
	g_data->status = 1;
}

void	exec_others(t_node_n *n)
{
	set_signal_def();
	g_data->pid = fork();
	if (g_data->pid < 0)
	{
		perror("fork");
		g_data->status = 1;
		return ;
	}
	else if (g_data->pid == 0)
		exec_others_sub(n);
	else
	{
		set_signal_ign();
		wait(&g_data->wstatus);
		wait_signal();
		set_status(g_data->wstatus);
	}
}

void	exec_others_sans_fork(t_node_n *n)
{
	g_data->cmd_error = ft_strdup(n->cmds[0]);
	if (n->cmds[0] != NULL)
		n->cmds[0] = search_path(n->cmds[0]);
	if (n->cmds[0] == NULL)
	{
		error_write("minishell: %s: command not found\n", g_data->cmd_error, 2);
		free(g_data->cmd_error);
		exit(2);
	}
	free(g_data->cmd_error);
	execve(n->cmds[0], n->cmds, g_data->envp);
	perror("execve");
	g_data->status = 1;
}
