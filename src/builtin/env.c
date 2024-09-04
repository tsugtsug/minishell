/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:42:58 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:10:01 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_blt(t_node_n *n)
{
	size_t	i;

	if (n->cmds[1] != NULL)
	{
		error_write("minishell: env: %s: no arguments are required.\n",
			n->cmds[1], 1);
		return ;
	}
	i = 0;
	while (g_data->envp[i])
	{
		if (ft_strchr(g_data->envp[i], '='))
			printf("%s\n", g_data->envp[i]);
		i += 1;
	}
	g_data->status = 0;
}
