/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 04:53:53 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:21:51 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_join2(t_token_l *lst, t_token_n *node, char *s1, char *s2)
{
	size_t		len1;
	size_t		len2;
	char		*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (0);
	ft_strlcpy(str, s1, (len1 + 1));
	ft_strlcat(str, s2, (len1 + len2 + 1));
	free(s1);
	node->word = str;
	delete_helper(lst, node->next);
	return (1);
}

int	word_join(t_token_l *lst)
{
	t_token_n	*tmp;

	tmp = lst->top;
	while (tmp != NULL)
	{
		if (tmp->type == STR && (tmp->next != NULL && tmp->next->type == STR))
		{
			if (!word_join2(lst, tmp, tmp->word, tmp->next->word))
			{
				token_free(lst);
				return (0);
			}
		}
		else
			tmp = tmp->next;
	}
	return (1);
}
