/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:34:39 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/06 00:43:19 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_envnode(t_env_lst *lst, t_env_node *node)
{
	t_env_node	*tmp;

	tmp = node;
	if (node->prev == NULL && node->next == NULL)
		lst->top = NULL;
	else if (node == lst->top)
	{
		lst->top = lst->top->next;
		lst->top->prev = NULL;
	}
	else if (node->next == NULL)
		node->prev->next = NULL;
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(tmp->key);
	if (tmp->value != NULL)
		free(tmp->value);
	free(tmp);
	lst->size -= 1;
}

static void	reset_sortnode(t_env_lst *lst, size_t count)
{
	t_env_node	*node;

	node = lst->top;
	while (node != NULL)
	{
		if (node->sort_n > count)
			node->sort_n -= 1;
		node = node->next;
	}
}

static void	unset_error_message(char **strs)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (strs[i])
	{
		if (!(ft_isalpha(strs[i][0]) || strs[i][0] == '_'))
		{
			unset_error_message2(strs[i]);
			return ;
		}
		j = 0;
		while (strs[i][j])
		{
			if (ft_strchr("!\"#$%&'()-|`@{}[];+:*<,>./?=", strs[i][j]))
			{
				unset_error_message2(strs[i]);
				return ;
			}
			j += 1;
		}
		i += 1;
	}
	g_data->status = 0;
}

int	unset_blt2(char *s)
{
	t_env_node	*envn;

	envn = g_data->envlst->top;
	while (envn != NULL)
	{
		if (ft_strcmp("_", s) != 0 && !ft_strcmp(envn->key, s))
		{
			reset_sortnode(g_data->envlst, envn->sort_n);
			delete_envnode(g_data->envlst, envn);
			if (!envp_re_create(g_data->envlst))
				return (0);
			break ;
		}
		else
			envn = envn->next;
	}
	return (1);
}

int	unset_blt(t_node_n *n)
{
	size_t		i;

	unset_error_message(&n->cmds[1]);
	i = 1;
	while (n->cmds[i] && n->cmds[1] != NULL)
	{
		if (!unset_blt2(n->cmds[i]))
			return (0);
		i += 1;
	}
	return (1);
}
