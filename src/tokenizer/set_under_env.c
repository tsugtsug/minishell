/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_under_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:23:04 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/06 01:51:31 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*value_set(t_token_l *lst)
{
	t_token_n	*last;
	char		*value;

	last = lst->top;
	while (last->next != NULL)
		last = last->next;
	if (lst->size > 1 && identifier_check(last->word)
		&& (!ft_strcmp(lst->top->word, "export")))
		value = ft_strndup(last->word, equal_len(last->word));
	else
		value = ft_strdup(last->word);
	return (value);
}

static t_env_node	*set_under_env2(t_token_l *lst)
{
	t_env_node	*env;
	char		*key;
	char		*value;

	value = value_set(lst);
	if (value == NULL)
		return (NULL);
	key = ft_strdup("_");
	if (key == NULL)
	{
		free(value);
		return (NULL);
	}
	env = envnode_new(key, value);
	if (env == NULL)
	{
		free(value);
		free(key);
		return (NULL);
	}
	return (env);
}

int	set_under_env(t_token_l *lst)
{
	t_env_node	*env;

	env = check_envp("_");
	if (env != NULL)
		delete_envnode(g_data->envlst, env);
	env = set_under_env2(lst);
	if (env == NULL)
		return (0);
	envlst_add(g_data->envlst, env);
	if (!envp_re_create(g_data->envlst))
	{
		delete_envnode(g_data->envlst, env);
		return (0);
	}
	return (1);
}
