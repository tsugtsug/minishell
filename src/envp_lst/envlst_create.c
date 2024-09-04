/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:51:25 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/10 17:00:19 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstsort_num(t_env_lst *lst)
{
	t_env_node	*node;
	t_env_node	*node2;
	size_t		count;

	node = lst->top;
	while (node != NULL)
	{
		node2 = lst->top;
		count = 1;
		while (node2 != NULL)
		{
			if (ft_strcmp(node->key, node2->key) > 0)
				count += 1;
			node2 = node2->next;
		}
		node->sort_n = count;
		node = node->next;
	}
}

int	key_value_add(t_env_lst *lst, char *str)
{
	char		*key;
	char		*value;
	t_env_node	*new;

	key = ft_strndup(str, equal_len(str));
	value = ft_strdup(&str[ft_strlen(key) + 1]);
	new = envnode_new(key, value);
	if (key == NULL || value == NULL || new == NULL)
	{
		if (key != NULL)
			free(key);
		if (value != NULL)
			free(value);
		if (new != NULL)
			free(new);
		return (0);
	}
	envlst_add(lst, new);
	return (1);
}

int	envlst_create(char **envp)
{
	size_t		i;

	g_data->envlst = envlst_new();
	if (g_data->envlst == NULL)
		return (0);
	i = 0;
	while (envp[i])
	{
		if (!key_value_add(g_data->envlst, envp[i]))
		{
			envlst_free();
			return (0);
		}
		i += 1;
	}
	if (!cumbersome_env(g_data->envlst))
	{
		envlst_free();
		return (0);
	}
	lstsort_num(g_data->envlst);
	return (1);
}
