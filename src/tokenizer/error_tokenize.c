/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:00:41 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/06 08:32:57 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_write_syntax(t_token_n *node, int flag)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (flag == 1)
		ft_putstr_fd(node->word, 2);
	else if (flag == 2)
		ft_putstr_fd(node->next->word, 2);
	else if (flag == 3)
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	g_data->status = 258;
	return (1);
}

static int	quart_return_flag(t_token_n *tmp)
{
	int		flag;

	flag = 0;
	while (tmp != NULL)
	{
		if (flag == 0)
		{
			if (tmp->type == QUOTE)
				flag = QUOTE;
			else if (tmp->type == QQUOTE)
				flag = QQUOTE;
		}
		else if (flag == QUOTE && tmp->type == QUOTE)
			flag = 0;
		else if (flag == QQUOTE && tmp->type == QQUOTE)
			flag = 0;
		tmp = tmp->next;
	}
	return (flag);
}

int	error_quart(t_token_l *lst)
{
	t_token_n	*tmp;
	int			flag;

	tmp = lst->top;
	flag = quart_return_flag(tmp);
	if (flag == QUOTE)
	{
		error_write("minishell: syntax error near unclosed single quote\n",
			NULL, 258);
		token_free(lst);
		return (0);
	}
	else if (flag == QQUOTE)
	{
		error_write("minishell: syntax error near unclosed double quote\n",
			NULL, 258);
		token_free(lst);
		return (0);
	}
	return (1);
}

static int	syntax_return_flag(t_token_n *node)
{
	if (node->type == PIPE)
	{
		if (node->next == NULL)
			return (1);
		else if ((node->next->type >= R && node->next->type <= LL))
			return (3);
		else if (node->next->type == PIPE)
			return (2);
	}
	if (node->type >= R && node->type <= LL)
	{
		if (node->next == NULL)
			return (3);
		else if ((node->next->type != STR) || node->next->type == PIPE
			|| (node->next->type >= R && node->next->type <= LL))
			return (2);
	}
	return (0);
}
// {
// 	if (node->next == NULL && node->type == PIPE)
// 		return (1);
// 	if (node->type == PIPE && node->next != NULL)
// 	{
// 		if ((node->next->type >= R && node->next->type <= LL))
// 			return (3);
// 		else if (node->next->type == PIPE)
// 			return (2);
// 	}
// 	if (node->type >= R && node->type <= LL)
// 	{
// 		if (node->next == NULL)
// 			return (3);
// 		else if ((node->next->type != STR) || node->next->type == PIPE
// 			|| (node->next->type >= R && node->next->type <= LL))
// 			return (2);
// 	}
// 	return (0);
// }

int	syntax_error(t_token_l *lst)
{
	t_token_n	*node;
	int			flag;

	node = lst->top;
	flag = 0;
	while (node != NULL)
	{
		flag = syntax_return_flag(node);
		if (flag != 0)
			break ;
		node = node->next;
	}
	if (flag != 0)
	{
		error_write_syntax(node, flag);
		token_free(lst);
		return (0);
	}
	return (1);
}
