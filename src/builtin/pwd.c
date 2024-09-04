/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 00:48:56 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/31 23:11:45 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_cmds_size(t_node_n *n)
{
	size_t	i;

	i = 0;
	if (n->cmds == NULL)
		return (0);
	while (n->cmds[i])
		i++;
	return (i);
}

static int	pwd_blt_sub(t_node_n *n)
{
	int	i;

	if (get_cmds_size(n) != 1 && n->cmds[1][0] == '-')
	{
		i = 1;
		while (n->cmds[1][i])
		{
			if (ft_isalnum(n->cmds[1][i]) || i == 3)
				break ;
			i++;
		}
		if (ft_isalnum(n->cmds[1][i]) || i == 3)
		{
			printf("minishell: pwd: -%c: invalid option\n", n->cmds[1][1]);
			printf("pwd: usage: pwd [no option]\n");
			g_data->status = 1;
			return (1);
		}
	}
	return (0);
}

void	pwd_blt(t_node_n *n)
{
	char	path[4096];

	if (pwd_blt_sub(n) == 1)
		return ;
	if (getcwd(path, sizeof(path)) != NULL)
	{
		printf("%s\n", path);
		g_data->status = 0;
	}
	else
	{
		perror("getcwd");
		g_data->status = 1;
	}
}
