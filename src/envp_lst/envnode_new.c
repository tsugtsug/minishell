/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envnode_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:36 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:16:59 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*envnode_new(char *key, char *value)
{
	t_env_node	*new;

	new = malloc(sizeof(t_env_node));
	if (new == NULL)
	{
		free(key);
		key = NULL;
		if (value != NULL)
		{
			free(value);
			value = NULL;
		}
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
