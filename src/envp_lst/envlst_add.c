/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:13:03 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/01 01:41:31 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envlst_add(t_env_lst *lst, t_env_node *node)
{
	t_env_node	*last;

	last = lst->top;
	if (lst->top == NULL)
		lst->top = node;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = node;
		node->prev = last;
	}
	lst->size += 1;
}
