/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 04:29:00 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/03 04:32:11 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str)
{
	t_env_node	*node;

	node = g_data->envlst->top;
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, str))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}
