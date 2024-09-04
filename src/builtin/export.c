/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:51:59 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/10 16:58:04 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(void)
{
	size_t		i;
	size_t		size;
	t_env_node	*envn;

	i = 1;
	size = g_data->envlst->size;
	while (i <= size)
	{
		envn = g_data->envlst->top;
		while (envn != NULL)
		{
			if (i == envn->sort_n && ft_strcmp(envn->key, "_") != 0)
			{
				printf("declare -x %s", envn->key);
				if (envn->value != NULL)
					printf("=\"%s\"\n", envn->value);
				else
					printf("\n");
				break ;
			}
			envn = envn->next;
		}
		i += 1;
	}
}

int	export_add2(char *key, char *value)
{
	t_env_node	*envn;

	envn = check_envp(key);
	if (envn != NULL)
	{
		free(key);
		if (value != NULL)
		{
			if (value != NULL)
			{
				free(envn->value);
				envn->value = value;
			}
		}
	}
	else
	{
		envn = envnode_new(key, value);
		if (envn == NULL)
		{
			return (0);
		}
		envlst_add(g_data->envlst, envn);
	}
	return (1);
}

int	export_add(char **cmds, size_t i)
{
	char		*key;
	char		*value;

	key = ft_strndup(cmds[i], equal_len(cmds[i]));
	if (key == NULL)
		return (0);
	if (cmds[i][equal_len(cmds[i])] == '=')
	{
		value = ft_strdup(&cmds[i][equal_len(cmds[i]) + 1]);
		if (value == NULL)
		{
			free(key);
			key = NULL;
			return (0);
		}
	}
	else
		value = NULL;
	if (!export_add2(key, value))
		return (0);
	key = NULL;
	value = NULL;
	return (1);
}

int	export_blt2(char **cmds, int *f)
{
	size_t		i;

	i = 1;
	while (cmds[i])
	{
		if (!identifier_check(cmds[i]))
		{
			error_write("minishell: export: `%s': not a valid identifier\n",
				cmds[i], 1);
			*f = 1;
			i += 1;
			continue ;
		}
		if (!export_add(cmds, i))
			return (0);
		i += 1;
		lstsort_num(g_data->envlst);
	}
	if (!envp_re_create(g_data->envlst))
		return (0);
	return (1);
}

int	export_blt(t_node_n *n)
{
	int		f;

	f = 0;
	if (n->cmds[1] == NULL)
		print_export();
	else
	{
		if (!export_blt2(n->cmds, &f))
			return (0);
	}
	if (f == 0)
		g_data->status = 0;
	return (1);
}
