/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:40:27 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/10 20:28:25 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_helper(t_token_l *lst, t_token_n *node)
{
	t_token_n	*free_node;

	free_node = node;
	free(node->word);
	if (node->prev == NULL && node->next == NULL)
		lst->top = NULL;
	else if (node->prev == NULL)
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
	free(free_node);
	lst->size -= 1;
}

void	delete_node(t_token_l *lst)
{
	t_token_n	*tmp;

	if (lst->top == NULL || (lst->top->next == NULL
			&& lst->top->word[0] == '\0'))
		return ;
	tmp = lst->top;
	while (tmp != NULL)
	{
		if (tmp->type >= SPACE1)
		{
			delete_helper(lst, tmp);
			tmp = lst->top;
		}
		else
			tmp = tmp->next;
	}
}
