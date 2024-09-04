/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 00:47:58 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/31 23:09:38 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_option_check(char *cmd)
{
	size_t		i;

	if (cmd == NULL)
		return (0);
	if (ft_strncmp(cmd, "-n", 2) != 0)
		return (0);
	i = 2;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i += 1;
	}
	return (1);
}

void	echo_blt(t_node_n *n)
{
	size_t	i;
	int		flag;

	i = 1;
	flag = 0;
	if (echo_option_check(n->cmds[i]))
	{
		flag = 1;
		while (n->cmds[i] && echo_option_check(n->cmds[i]))
			i += 1;
	}
	while (n->cmds[i])
	{
		printf("%s", n->cmds[i]);
		i += 1;
		if (n->cmds[i] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	g_data->status = 0;
}
