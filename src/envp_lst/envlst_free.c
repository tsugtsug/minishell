/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:47:41 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:16:25 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pop(t_env_lst *lst)
{
	t_env_node	*free_node;

	if (lst->size == 0)
		return (0);
	free_node = lst->top;
	if (lst->size == 1)
		lst->top = NULL;
	else
	{
		lst->top = lst->top->next;
		lst->top->prev = NULL;
	}
	if (free_node->value != NULL)
		free(free_node->value);
	free(free_node->key);
	free(free_node);
	lst->size--;
	return (1);
}

void	envlst_free(void)
{
	if (g_data->envlst == NULL)
		return ;
	while (g_data->envlst->top != NULL)
	{
		pop(g_data->envlst);
	}
	free(g_data->envlst);
	g_data->envlst = NULL;
}
