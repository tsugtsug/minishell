/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 05:26:12 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:21:06 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_free(t_token_l *lst)
{
	t_token_n	*free_n;
	t_token_n	*tmp;

	if (lst == NULL)
		return ;
	tmp = lst->top;
	while (tmp != NULL)
	{
		free_n = tmp;
		tmp = tmp->next;
		free(free_n->word);
		free(free_n);
	}
	lst->top = NULL;
	lst->size = 0;
	free(lst);
	lst = NULL;
}
