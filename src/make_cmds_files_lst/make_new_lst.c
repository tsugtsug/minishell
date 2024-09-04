/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:01:52 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/23 03:26:32 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(void)
{
	t_token_n	*p;
	t_token_n	*tmp;

	p = g_data->tok->top;
	while (p != NULL)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
	g_data->tok->top = NULL;
	g_data->tok->size = 0;
}

void	make_new_lst(t_token_n *until)
{
	t_token_n	*p;
	t_token_n	*tmp;
	size_t		i;

	p = g_data->tok->top;
	i = 0;
	while (p != until)
	{
		tmp = p->next;
		free(p);
		p = tmp;
		i++;
	}
	tmp = p->next;
	free(p->word);
	free(p);
	p = tmp;
	if (p != NULL)
		p->prev = NULL;
	g_data->tok->size -= (i + 1);
	g_data->tok->top = p;
}
