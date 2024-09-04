/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cumbersome_env2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:27:10 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/10 17:29:48 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shlvl2(t_env_lst *lst, t_env_node *n)
{
	char		*key;
	char		*value;

	key = NULL;
	value = NULL;
	key = ft_strdup("SHLVL");
	if (key == NULL)
		return (0);
	value = ft_strdup("1");
	if (value == NULL)
	{
		free(key);
		return (0);
	}
	n = envnode_new(key, value);
	if (n == NULL)
	{
		free(key);
		free(value);
		return (0);
	}
	envlst_add(lst, n);
	return (1);
}

int	shlvl(t_env_lst *lst)
{
	t_env_node	*n;
	long		num;

	n = check_envp("SHLVL");
	if (n == NULL)
	{
		if (!shlvl2(lst, n))
			return (0);
	}
	else
	{
		if (n->value != NULL)
		{
			num = ft_atol(n->value) + 1;
			free(n->value);
		}
		else
			num = 1;
		n->value = ft_ltoa(num);
		if (n->value == NULL)
			return (0);
	}
	return (1);
}

static int	under2(t_env_lst *lst, t_env_node *n)
{
	char		*key;
	char		*value;

	key = NULL;
	value = NULL;
	key = ft_strdup("_");
	if (key == NULL)
		return (0);
	value = ft_strdup("./minishell");
	if (value == NULL)
	{
		free(key);
		return (0);
	}
	n = envnode_new(key, value);
	if (n == NULL)
	{
		free(key);
		free(value);
		return (0);
	}
	envlst_add(lst, n);
	return (1);
}

int	under(t_env_lst *lst)
{
	t_env_node	*n;

	n = check_envp("_");
	if (n == NULL)
	{
		if (!under2(lst, n))
			return (0);
	}
	else
	{
		if (n->value != NULL)
			free(n->value);
		n->value = ft_strdup("./minishell");
		if (n->value == NULL)
			return (0);
	}
	return (1);
}
