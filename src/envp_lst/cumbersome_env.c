/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cumbersome_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:59:14 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/10 17:34:26 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	oldpwd(t_env_lst *lst)
{
	t_env_node	*n;
	char		*key;

	key = NULL;
	n = check_envp("OLDPWD");
	if (n == NULL)
	{
		key = ft_strdup("OLDPWD");
		if (key == NULL)
			return (0);
		n = envnode_new(key, NULL);
		if (n == NULL)
		{
			free(key);
			return (0);
		}
		envlst_add(lst, n);
	}
	else
	{
		if (n->value != NULL)
			free(n->value);
		n->value = NULL;
	}
	return (1);
}

static int	pwd2(t_env_lst *lst, t_env_node *n, char path[4096])
{
	char		*key;
	char		*value;

	key = NULL;
	value = NULL;
	key = ft_strdup("PWD");
	if (key == NULL)
		return (0);
	value = ft_strdup(path);
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

int	pwd(t_env_lst *lst)
{
	t_env_node	*n;
	char		path[4096];

	getcwd(path, sizeof(path));
	n = check_envp("PWD");
	if (n == NULL)
	{
		if (!pwd2(lst, n, path))
			return (0);
	}
	else
	{
		if (ft_strcmp(n->value, path) != 0)
		{
			if (n->value != NULL)
				free(n->value);
			n->value = ft_strdup(path);
			if (n->value == NULL)
				return (0);
		}
	}
	return (1);
}

int	cumbersome_env(t_env_lst *lst)
{
	if (!oldpwd(lst))
	{
		envlst_free();
		return (0);
	}
	if (!pwd(lst))
	{
		envlst_free();
		return (0);
	}
	if (!shlvl(lst))
	{
		envlst_free();
		return (0);
	}
	if (!under(lst))
	{
		envlst_free();
		return (0);
	}
	return (1);
}
