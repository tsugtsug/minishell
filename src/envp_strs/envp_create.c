/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 06:56:54 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/03 03:44:00 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_all_free(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i += 1;
	}
	free(strs);
	strs = NULL;
}

int	envp_re_create(t_env_lst *lst)
{
	size_t			i;
	t_env_node		*tmp;

	envp_all_free(g_data->envp);
	g_data->envp = malloc(sizeof(char *) * (lst->size + 1));
	if (g_data->envp == NULL)
	{
		return (0);
	}
	i = 0;
	tmp = lst->top;
	while (tmp != NULL)
	{
		g_data->envp[i] = equal_join(tmp->key, tmp->value);
		if (g_data->envp[i] == NULL)
		{
			envp_all_free(g_data->envp);
			return (0);
		}
		i += 1;
		tmp = tmp->next;
	}
	g_data->envp[i] = NULL;
	return (1);
}

int	envp_create(t_env_lst *lst)
{
	size_t			i;
	t_env_node		*tmp;

	g_data->envp = malloc(sizeof(char *) * (lst->size + 1));
	if (g_data->envp == NULL)
		return (0);
	i = 0;
	tmp = lst->top;
	while (tmp != NULL)
	{
		g_data->envp[i] = equal_join(tmp->key, tmp->value);
		if (g_data->envp[i] == NULL)
		{
			envp_all_free(g_data->envp);
			return (0);
		}
		i += 1;
		tmp = tmp->next;
	}
	g_data->envp[i] = NULL;
	return (1);
}
