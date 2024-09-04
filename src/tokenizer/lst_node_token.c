/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_node_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 03:48:13 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:19:56 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_add(t_token_l *lst, char *str)
{
	t_token_n	*tmp;
	t_token_n	*new;

	new = token_n_new(str);
	if (new == NULL)
		return (0);
	if (lst->top == NULL)
		lst->top = new;
	else
	{
		tmp = lst->top;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	lst->size += 1;
	return (1);
}

t_token_n	*token_n_new(char *s)
{
	t_token_n	*new;

	new = malloc(sizeof(t_token_n));
	if (new == NULL)
		return (NULL);
	new->word = s;
	new->type = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token_l	*token_lst_new(void)
{
	t_token_l	*lst;

	lst = malloc(sizeof(t_token_l));
	if (lst == NULL)
		return (NULL);
	lst->top = NULL;
	lst->size = 0;
	return (lst);
}
