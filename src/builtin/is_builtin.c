/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:41:06 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 01:41:58 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(t_node_n *n)
{
	char	*name;

	if (n->cmds[0] == NULL)
		return ;
	name = n->cmds[0];
	if (ft_strcmp(name, "echo") == 0)
		n->blt = ECHO_NUM;
	if (ft_strcmp(name, "cd") == 0)
		n->blt = CD_NUM;
	if (ft_strcmp(name, "pwd") == 0)
		n->blt = PWD_NUM;
	if (ft_strcmp(name, "export") == 0)
		n->blt = EXPORT_NUM;
	if (ft_strcmp(name, "unset") == 0)
		n->blt = UNSET_NUM;
	if (ft_strcmp(name, "env") == 0)
		n->blt = ENV_NUM;
	if (ft_strcmp(name, "exit") == 0)
		n->blt = EXIT_NUM;
}
