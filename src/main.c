/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:53:42 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/13 00:24:07 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*g_data;

void	g_data_init(void)
{
	g_data = (t_data *)malloc(sizeof(t_data));
	if (!g_data)
		exit (1);
	g_data->status = 0;
	g_data->line = NULL;
	g_data->tok = NULL;
	g_data->envlst = NULL;
	g_data->save_in = dup(STDIN_FILENO);
	g_data->save_out = dup(STDOUT_FILENO);
	g_data->node_head.size = 0;
	g_data->node_head.top = NULL;
	g_data->pipe_count = 0;
	g_data->envp = NULL;
	g_data->signal = 0;
}

int	minishell_start(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd("minishell: requires no arguments\n", 2);
		exit (1);
	}
	g_data_init();
	g_data->envp = envp;
	if (!envlst_create(envp))
	{
		free (g_data);
		return (0);
	}
	if (!envp_create(g_data->envlst))
	{
		envlst_free();
		free (g_data);
		return (0);
	}
	return (1);
}

void	tok_judge(void)
{
	if (g_data->tok->top != NULL)
		make_cmds_and_exec();
	else
	{
		free(g_data->tok);
		g_data->tok = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (!minishell_start(argc, argv, envp))
		return (1);
	while (1)
	{
		set_signal_main();
		g_data->line = readline("minishell$ ");
		if (g_data->line == NULL)
			break ;
		if (*g_data->line)
			add_history(g_data->line);
		if (!check_line(g_data->line))
			continue ;
		g_data->line = expand_line(g_data->line);
		if (g_data->line == NULL)
			continue ;
		if (tokenizer() == 0)
			continue ;
		tok_judge();
		free(g_data->line);
	}
	last_free();
}
